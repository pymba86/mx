#ifndef MX_TOPIC_HPP
#define MX_TOPIC_HPP

#include <string_view>
#include <mx/session/session.hpp>
#include <unordered_set>

namespace mx {

    class broker_topic {
    public:
        broker_topic();

        explicit broker_topic(std::string_view topic);
        ~broker_topic();
        bool add_session(const std::shared_ptr<session>& session);
        bool remove_session(const std::shared_ptr<session>& session);

        const std::string& get_topic() const;
        const std::unordered_set<std::shared_ptr<session>>& get_sessions();

    private:
        const std::string m_topic;
        std::unordered_set<std::shared_ptr<session>> m_sessions;
    };

    inline broker_topic::broker_topic(): m_topic(), m_sessions() {

    }

    inline broker_topic::broker_topic(std::string_view topic) : m_topic(topic), m_sessions() {

    }

    inline broker_topic::~broker_topic() {

    }

    inline bool broker_topic::add_session(const std::shared_ptr<session> &session) {
        auto result = m_sessions.insert(session);
        return result.second;
    }

    inline bool broker_topic::remove_session(const std::shared_ptr<session> &session) {
        return m_sessions.erase(session) != 0;
    }

    inline const std::string& broker_topic::get_topic() const {
        return m_topic;
    }

    inline const std::unordered_set<std::shared_ptr<session>> &broker_topic::get_sessions() {
        return m_sessions;
    }


}

#endif //MX_TOPIC_HPP
