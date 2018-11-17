//
// Created by pymba86 on 18.11.18.
//

#include <boost/asio.hpp>
#include <memory>
#include <unordered_map>
#include <mx/broker/broker.hpp>

#ifndef MX_ROUTER_IMPL_HPP
#define MX_ROUTER_IMPL_HPP

namespace mx {


    class router_impl {
    public:

        router_impl(boost::asio::io_service& io_service, const std::string& realm);
        ~router_impl() = default;

        const std::string& get_realm() const;
        const std::shared_ptr<generator>& get_session_id_generator() const;

        void process_subscribe_message(const session_id& session_id, subscribe_message* subscribe_message);

        void process_publish_message(const session_id& session_id,
                                     publish_message* publish_message);

        bool has_session(const session_id& session_id);
        void close_session(const session_id& session_id, const std::string& reason);
        bool attach_session(const std::shared_ptr<session>& session);
        bool detach_session(const session_id & session_id);

    private:
        std::string m_realm;

        broker m_broker;

        std::shared_ptr<generator> m_session_id_generator;
        std::unordered_map<session_id, std::shared_ptr<session>> m_sessions;
    };
}

#endif //MX_ROUTER_IMPL_HPP
