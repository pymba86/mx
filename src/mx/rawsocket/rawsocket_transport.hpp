
#ifndef MX_RAWSOCKET_TRANSPORT_HPP
#define MX_RAWSOCKET_TRANSPORT_HPP

#include <mx/transport/transport.hpp>
#include <mx/serialization/serializer.hpp>
#include <mx/rawsocket/rawsocket_connection.hpp>
#include <mx/serialization/expandable_buffer.hpp>
#include <utility>


namespace mx {

    class message;

    class rawsocket_transport : public transport {
    public:
        rawsocket_transport(std::shared_ptr<serializer> serializer,
                            std::shared_ptr<rawsocket_connection> connection);

        ~rawsocket_transport() override = default;

        bool send_message(message &&message) override;

    private:
        std::shared_ptr<serializer> m_serializer;
        std::shared_ptr<rawsocket_connection> m_connection;
    };

    rawsocket_transport::rawsocket_transport(std::shared_ptr<serializer> serializer,
                                             std::shared_ptr<rawsocket_connection> connection)
            : m_serializer(std::move(serializer)), m_connection(std::move(connection)) {

    }

    bool rawsocket_transport::send_message(message &&message) {
        MX_TRACE("sending message: %1%", message_type_to_string(message.get_type()));
        expandable_buffer buffer = m_serializer->serialize(message);
        return m_connection->send_message(buffer.data(),buffer.size());
    }
}

#endif //MX_RAWSOCKET_TRANSPORT_HPP
