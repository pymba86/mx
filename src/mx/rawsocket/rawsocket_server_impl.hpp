#ifndef MX_RAWSOCKET_SERVER_IMPL_HPP
#define MX_RAWSOCKET_SERVER_IMPL_HPP

#include <memory>
#include <mx/process/process.hpp>

#include "rawsocket_listener.hpp"

namespace mx {

    class manager;

    class serializers;

    class rawsocket_server_impl : public std::enable_shared_from_this<rawsocket_server_impl> {
    public:
        rawsocket_server_impl(const std::shared_ptr<manager> &manager,
                              const std::shared_ptr<serializers> &serializers);

        ~rawsocket_server_impl() = default;

        void attach_listener(const std::shared_ptr<rawsocket_listener> &listener);

        void start();

        void shutdown();

    private:
        void on_connect(const std::shared_ptr<rawsocket_connection> &connection);

        void on_handshake(const std::shared_ptr<rawsocket_connection> &connection,
                          uint32_t capabilities);

        void on_message(const std::shared_ptr<rawsocket_connection> &connection,
                        const char *buffer, size_t length);

        void on_close(const std::shared_ptr<rawsocket_connection> &connection);

        void on_fail(const std::shared_ptr<rawsocket_connection> &connection, const char *reason);

        void teardown_connection(const std::shared_ptr<rawsocket_connection> &connection);

    private:
        std::shared_ptr<manager> m_manager;
        std::shared_ptr<serializers> m_serializers;

        std::set<std::shared_ptr<rawsocket_listener>,
                std::owner_less<std::shared_ptr<rawsocket_listener>>> m_listeners;

        std::set<std::shared_ptr<rawsocket_connection>,
                std::owner_less<std::shared_ptr<rawsocket_connection>>> m_connections;

        message_process m_message_process;
    };
}

#endif //MX_RAWSOCKET_SERVER_IMPL_HPP
