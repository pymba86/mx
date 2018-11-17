
#include "router.hpp"

namespace mx {

    mx::router::router(boost::asio::io_service &io_service, const std::string &realm)
            : m_impl(new router_impl(io_service, realm)) {
    }

    const std::string &router::get_realm() const {
        return m_impl->get_realm();
    }

    const std::shared_ptr<generator> &router::get_session_id_generator() const {
        return m_impl->get_session_id_generator();
    }

    bool router::has_session(const session_id &session_id) {
        return m_impl->has_session(session_id);
    }

    void router::close_session(const session_id &session_id, const std::string &reason) {
        m_impl->close_session(session_id, reason);
    }

    bool router::attach_session(const std::shared_ptr<session> &session) {
        return m_impl->attach_session(session);
    }

    bool router::detach_session(const session_id &session_id) {
        return m_impl->detach_session(session_id);
    }

    void router::process_subscribe_message(const session_id &session_id, subscribe_message *subscribe_message) {
        m_impl->process_subscribe_message(session_id, subscribe_message);
    }

    void router::process_publish_message(const session_id &session_id, publish_message *publish_message) {
        m_impl->process_publish_message(session_id, publish_message);
    }


}