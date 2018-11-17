

#include "router.hpp"
#include <mx/trace/trace.hpp>

namespace mx {

    router_impl::router_impl(boost::asio::io_service &io_service, const std::string &realm)
            : m_realm(realm),
              m_broker(realm),
              m_session_id_generator(generator_factory::create(realm)),
              m_sessions() {

    }

    const std::string &router_impl::get_realm() const {
        return m_realm;
    }

    const std::shared_ptr<generator> &router_impl::get_session_id_generator() const {
        return m_session_id_generator;
    }

    bool router_impl::has_session(const session_id &session_id) {
        return m_sessions.find(session_id) != m_sessions.end();
    }

    void router_impl::close_session(const session_id &session_id, const std::string &reason) {

    }

    bool router_impl::attach_session(const std::shared_ptr<session> &session) {
        MX_TRACE("attaching session: %1%", *session);

        auto result = m_sessions.insert(
                std::make_pair(session->get_session_id(), session));

        if (result.second) {
            m_broker.attach_session(session);

            return true;
        }

        MX_TRACE("failed to attach session: %1%", *session);

        return false;

    }

    bool router_impl::detach_session(const session_id &session_id) {
        return false;
    }

    void router_impl::process_subscribe_message(const session_id &session_id, subscribe_message *subscribe_message) {
        m_broker.process_subscribe_message(session_id, subscribe_message);
    }

    void router_impl::process_publish_message(const session_id &session_id, publish_message *publish_message) {
        m_broker.process_publish_message(session_id, publish_message);
    }
}