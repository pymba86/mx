

#include "rawsocket_server.hpp"

namespace mx {

    mx::rawsocket_server::rawsocket_server(const std::shared_ptr<manager> &manager,
                                           const std::shared_ptr<serializers>& serializers) :
            m_impl(new rawsocket_server_impl(manager, serializers)) {
    }

    void rawsocket_server::attach_listener(const std::shared_ptr<rawsocket_listener>& listener) {
        m_impl->attach_listener(listener);
    }

    void rawsocket_server::start() {
        m_impl->start();
    }

    void rawsocket_server::shutdown() {
        m_impl->shutdown();

    }


}
