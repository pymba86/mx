
#include "broker.hpp"
#include <mx/trace/trace.hpp>

namespace mx {

    broker::broker(std::string_view realm)
            : m_realm(realm),
              m_publication_id_generator(),
              m_subscription_id_generator(),
              m_sessions(),
              m_session_subscriptions(),
              m_topic_subscriptions(),
              m_subscription_topics() {
    }

    broker::~broker() {

    }

    void broker::attach_session(const std::shared_ptr<session> &session) {
        MX_TRACE("attach session: %1%", session);
        auto result = m_sessions.insert(
                std::make_pair(session->get_session_id(), session));
        if (!result.second) {
            throw std::logic_error("broker session already registered");
        }
    }

    void broker::detach_session(const session_id &id) {
        auto session_itr = m_sessions.find(id);
        if (session_itr == m_sessions.end()) {
            throw std::logic_error("broker session does not exist");
        }


        MX_TRACE("detach session: %1%", session_itr->second.get());
        auto session_subscriptions_itr = m_session_subscriptions.find(id);
        if (session_subscriptions_itr != m_session_subscriptions.end()) {
            MX_TRACE("cleaning up session subscriptions");
            for (const auto& subscription_id : session_subscriptions_itr->second) {
                auto subscription_topics_itr = m_subscription_topics.find(subscription_id);
                if (subscription_topics_itr == m_subscription_topics.end()) {
                    MX_TRACE("error: broker subscription topics are out of sync");
                    continue;
                }
                std::string topic = subscription_topics_itr->second->get_topic();
                MX_TRACE("cleaning up subscription topic");
                subscription_topics_itr->second->remove_session(session_itr->second);
                if (subscription_topics_itr->second->get_sessions().size() == 0) {
                    m_subscription_topics.erase(subscription_id);
                }

                auto topic_subscriptions_itr = m_topic_subscriptions.find(topic);
                if (topic_subscriptions_itr == m_topic_subscriptions.end()) {
                    MX_TRACE("error: broker topic subscriptions are out of sync");
                    continue;
                }

                MX_TRACE("cleaning up topic subscriptions");
                topic_subscriptions_itr->second->remove_subscription(subscription_id);
                if (topic_subscriptions_itr->second->get_subscriptions().size() == 0) {
                    m_topic_subscriptions.erase(topic);
                }
            }

            m_session_subscriptions.erase(session_subscriptions_itr);
        }

        m_sessions.erase(session_itr);
    }

    void broker::process_publish_message(const session_id &session_id, publish_message *publish_message) {

        auto session_itr = m_sessions.find(session_id);
        if (session_itr == m_sessions.end()) {
            throw std::logic_error("broker session does not exist");
        }

        //MX_TRACE("%1%, %2%", *session_itr->second % &publish_message);
    }

    void broker::process_subscribe_message(const session_id &session_id, subscribe_message *subscribe_message) {
        auto session_itr = m_sessions.find(session_id);
        if (session_itr == m_sessions.end()) {
            throw std::logic_error("broker session does not exist");
        }

       // MX_TRACE("%1%, %2%", *session_itr->second % &subscribe_message);
    }


}