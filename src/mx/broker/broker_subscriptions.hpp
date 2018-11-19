#ifndef MX_BROKER_SUBSCRIPTIONS_HPP
#define MX_BROKER_SUBSCRIPTIONS_HPP

#include <unordered_set>
#include <unordered_map>
#include <mx/session/session.hpp>

namespace mx {

    class broker_subscriptions {
    public:
        using subscriptions = std::unordered_map<subscription_id, std::shared_ptr<session>>;

        broker_subscriptions();
        ~broker_subscriptions();

        bool add_subscription(const subscription_id &id, const std::shared_ptr<session> &session);

        bool remove_subscription(const subscription_id &id);

        void remove_subscriptions(const std::shared_ptr<session> &session);

        const subscriptions get_subscriptions() const;

    private:
        subscriptions m_subscriptions;
    };

    inline broker_subscriptions::broker_subscriptions(): m_subscriptions() {

    }

    inline broker_subscriptions::~broker_subscriptions() {

    }

    inline    bool broker_subscriptions::add_subscription(const subscription_id &id, const std::shared_ptr<session> &session) {
        auto result = m_subscriptions.emplace(id, session);
        return result.second;
    }

    inline  bool broker_subscriptions::remove_subscription(const subscription_id &id) {
        return m_subscriptions.erase(id) != 0;
    }

    inline void broker_subscriptions::remove_subscriptions(const std::shared_ptr<session> &session) {
        auto itr = m_subscriptions.begin();
        auto end = m_subscriptions.end();
        while (itr != end) {
            if (itr->second == session) {
                itr = m_subscriptions.erase(itr);
                continue;
            }
            ++itr;
        }
    }

    inline const broker_subscriptions::subscriptions broker_subscriptions::get_subscriptions() const {
        return m_subscriptions;
    }

}

#endif //MX_BROKER_SUBSCRIPTIONS_HPP
