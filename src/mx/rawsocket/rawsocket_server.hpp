
#ifndef MX_RAWSOCKET_SERVER_HPP
#define MX_RAWSOCKET_SERVER_HPP

#include <memory>
#include "rawsocket_server_impl.hpp"

namespace mx {

    class manager;
    class rawsocket_listener;

    class serializers;

    class rawsocket_server {
    public:
        rawsocket_server(const std::shared_ptr<manager> &manager, const std::shared_ptr<serializers>& serializers);
        ~rawsocket_server() = default;

        void attach_listener(const std::shared_ptr<rawsocket_listener>& listener);
        void start();
        void shutdown();

    private:
        std::shared_ptr<rawsocket_server_impl> m_impl;
    };
}

#endif //MX_RAWSOCKET_SERVER_HPP
