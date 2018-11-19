//
// Created by pymba86 on 18.11.18.
//

#ifndef MX_TCP_LISTENER_HPP
#define MX_TCP_LISTENER_HPP

#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "rawsocket_listener.hpp"
#include "rawsocket_connection.hpp"

namespace mx {
    class tcp_listener : public rawsocket_listener, public std::enable_shared_from_this<tcp_listener> {
    public:
        tcp_listener(boost::asio::io_service& io_service, const boost::asio::ip::address& ip_address, uint16_t port);

        ~tcp_listener() override;

        void start_listening() override;
        void stop_listening() override;
        std::shared_ptr<rawsocket_connection> create_connection() override;

    protected:
        void async_accept() override;

    private:
        boost::asio::ip::tcp::socket m_socket;
        boost::asio::ip::tcp::acceptor m_acceptor;
        boost::asio::ip::tcp::endpoint m_endpoint;

    };
}

#endif //MX_TCP_LISTENER_HPP
