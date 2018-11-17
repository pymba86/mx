#ifndef MX_BROKER_HPP
#define MX_BROKER_HPP

#include <string>
#include <memory>

#include <unordered_map>
#include <unordered_set>

#include <mx/session/session.hpp>
#include <mx/utility/types.hpp>

#include <mx/message/protocol/publish_message.hpp>
#include <mx/message/protocol/subscribe_message.hpp>
#include <src/mx/identifiers/generator.hpp>
#include "topic.hpp"
#include "broker_subscriptions.hpp"

namespace mx {

    class broker {
    public:
        explicit broker(std::string_view realm);

        ~broker();

        void attach_session(const std::shared_ptr<session> &session);
        void detach_session(const session_id& id);

        void process_publish_message(const session_id& session_id,
                publish_message* publish_message);

        void process_subscribe_message(const session_id& session_id,
                                     subscribe_message* subscribe_message);

    private:
        const std::string m_realm;
        generator m_publication_id_generator;
        generator m_subscription_id_generator;
        std::unordered_map<session_id, std::shared_ptr<session>> m_sessions;
        std::unordered_map<session_id, std::unordered_set<subscription_id>> m_session_subscriptions;
        std::unordered_map<std::string, std::unique_ptr<broker_subscriptions>> m_topic_subscriptions;
        std::unordered_map<subscription_id, std::unique_ptr<broker_topic>> m_subscription_topics;
    };

}

#endif //MX_BROKER_HPP
