
#include <mx/rawsocket/rawsocket_server_impl.hpp>
#include <mx/trace/trace.hpp>
#include "rawsocket_server_impl.hpp"
#include <mx/rawsocket/rawsocket_connection.hpp>
#include <mx/serialization/serializers.hpp>
#include <mx/rawsocket/rawsocket_transport.hpp>
#include <mx/router/router.hpp>
#include <mx/router/router.hpp>
#include <mx/router/manager.hpp>

namespace mx {

    rawsocket_server_impl::rawsocket_server_impl(const std::shared_ptr<manager> &manager,
                                                 const std::shared_ptr<serializers> &serializers)
            : m_manager(manager), m_serializers(serializers),
              m_listeners(),
              m_connections(),
              m_message_process(manager) {


    }

    void rawsocket_server_impl::attach_listener(const std::shared_ptr<rawsocket_listener> &listener) {
        std::weak_ptr<rawsocket_server_impl> weak_self = shared_from_this();

        listener->set_error_handler(
                [weak_self](rawsocket_listener &listener, const boost::system::error_code &error_code) {
                    auto shared_self = weak_self.lock();
                    if (shared_self) {
                        assert(error_code);
                        if (error_code == boost::asio::error::operation_aborted) {
                            return;
                        }

                        assert(listener.is_listening());
                        MX_TRACE("rawsocket listener error: %1%", error_code.message());
                        listener.stop_listening();
                        listener.start_listening();

                    }
                });

        listener->set_accept_handler([weak_self](const std::shared_ptr<rawsocket_connection> &connection) {
            auto shared_self = weak_self.lock();
            if (shared_self) {
                shared_self->on_connect(connection);
            }
        });

        m_listeners.insert(listener);
    }

    void rawsocket_server_impl::start() {
        MX_TRACE("starting rawsocket server");
        assert(!m_listeners.empty());
        for (auto &listener : m_listeners) {
            listener->start_listening();
        }
    }

    void rawsocket_server_impl::shutdown() {
        MX_TRACE("stopping rawsocket server");
        for (auto &listener : m_listeners) {
            listener->stop_listening();
        }
    }

    void rawsocket_server_impl::on_connect(const std::shared_ptr<rawsocket_connection> &connection) {
        std::weak_ptr<rawsocket_server_impl> weak_self = shared_from_this();

        auto handshake_handler = [weak_self](const std::shared_ptr<rawsocket_connection> &connection,
                                             uint32_t capabilities) {
            auto shared_self = weak_self.lock();
            if (shared_self) {
                shared_self->on_handshake(connection, capabilities);
            }
        };

        connection->set_handshake_handler(handshake_handler);

        auto message_handler = [weak_self](
                const std::shared_ptr<rawsocket_connection> &connection,
                const char *buffer,
                size_t length) {
            auto shared_self = weak_self.lock();
            if (shared_self) {
                shared_self->on_message(connection, buffer, length);
            }
        };
        connection->set_message_handler(message_handler);

        auto close_handler = [weak_self](const std::shared_ptr<rawsocket_connection> &connection) {
            auto shared_self = weak_self.lock();
            if (shared_self) {
                shared_self->on_close(connection);
            }
        };
        connection->set_close_handler(close_handler);

        auto fail_handler = [weak_self](
                const std::shared_ptr<rawsocket_connection> &connection,
                const char *reason) {
            auto shared_self = weak_self.lock();
            if (shared_self) {
                shared_self->on_fail(connection, reason);
            }
        };
        connection->set_fail_handler(fail_handler);

        connection->async_handshake();
        m_connections.insert(connection);
    }

    void rawsocket_server_impl::on_handshake(const std::shared_ptr<rawsocket_connection> &connection,
                                             uint32_t capabilities) {
        // If the first octet is not the magic number 0x7F value then
        // this is not a valid capabilities exchange and we should fail
        // the connection. See the advanced specification for details on
        // the choice of this magic number.
        uint32_t magic = (capabilities & 0xFF000000) >> 24;
        if (magic != 0x7F) {
            MX_TRACE("invalid capabilities: %1%", capabilities);
            return teardown_connection(connection);
        }

        // TODO: Ignore the length for now. We will need to add this in at some point
        //       but currently the autobahn client ignores it anyways. It will need
        //       to get cached in the connection properties.
        //uint32_t exponent = ((capabilities & 0x00F00000) >> 20) + 9;
        //uint32_t max_message_length = 1 << exponent;

        // Currently we only support msgpack serialization. If this changes we will
        // need to make sure that the requested serialization protocol is cached in
        // the connection properties so that the correct serializer can be associated
        // with the connection for message processing.
        uint32_t serializer = (capabilities & 0x000F0000) >> 16;
        if (serializer != 0x2) {
            MX_TRACE("invalid serializer specified: %1%", serializer);
            if (!connection->send_handshake(htonl(0x7F100000))) {
                MX_TRACE("failed to send handshake response to component: network failure");
                teardown_connection(connection);
            }
            return;
        }

        // Make sure that the reserved bits are all zeros as expected otherwise
        // send an error response back in the returned handshake.
        uint32_t reserved = capabilities & 0x0000FFFF;
        if (reserved != 0) {
            if (!connection->send_handshake(htonl(0x7F300000))) {
                MX_TRACE("failed to send handshake response to component: network failure");
                teardown_connection(connection);
            }
            return;
        }

        // TODO: For now just echo back the clients capabilities. Once we
        //       decide to support a maximum message length we will have
        //       to report that back to the client here.
        if (connection->send_handshake(htonl(capabilities))) {
            // Prepare the connection to start receiving wamp messages. We only have to
            // initiate this once and it will then continue to re-arm itself after each
            // message is received. This is effectively what switches us from a handshake
            // receiving state to a message receiving state.
            connection->async_receive();
        } else {
            MX_TRACE("failed to send handshake response to component: network failure");
            teardown_connection(connection);
        }
    }

    void rawsocket_server_impl::on_message(const std::shared_ptr<rawsocket_connection> &connection, const char *buffer,
                                           size_t length) {
        try {
            std::shared_ptr<serializer> serializer =
                    m_serializers->get_serializer(serializer_type::msgpack);

            std::unique_ptr<message> message(
                    serializer->deserialize(buffer, length));

            std::unique_ptr<transport> transport(
                    new rawsocket_transport(serializer, connection));

            if (message) {
                m_message_process.process_message(message, std::move(transport), connection.get());
            }
        } catch (const std::exception &e) {
            MX_TRACE("unhandled exception: %1%", e.what());
        }

    }

    void rawsocket_server_impl::on_close(const std::shared_ptr<rawsocket_connection> &connection) {
        teardown_connection(connection);
    }

    void rawsocket_server_impl::on_fail(const std::shared_ptr<rawsocket_connection> &connection, const char *reason) {
        teardown_connection(connection);
    }

    void rawsocket_server_impl::teardown_connection(const std::shared_ptr<rawsocket_connection> &connection) {
        if (connection->has_session_id()) {
            std::shared_ptr<router> router = m_manager->get_router(connection->get_realm());
            if (router) {
                router->detach_session(connection->get_session_id());
            }
        }
        m_connections.erase(connection);
    }
}