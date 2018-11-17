#ifndef MX_ROUTER_HPP
#define MX_ROUTER_HPP

#include <string>
#include <forward_list>
#include <mx/process/process.hpp>
#include <unordered_set>
#include <unordered_map>
#include <mx/utility/types.hpp>
#include <mx/session/session.hpp>
#include <mx/broker/broker.hpp>
#include <boost/asio.hpp>
#include "router_impl.hpp"

namespace mx {
    class router {
    public:

        router(boost::asio::io_service& io_service, const std::string& realm);
        ~router() = default;

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
        std::unique_ptr<router_impl> m_impl;
    };
}


#endif //MX_ROUTER_HPP
