//
// Created by pymba86 on 18.11.18.
//

#ifndef MX_TCP_CONNECTION_HPP
#define MX_TCP_CONNECTION_HPP

#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include "rawsocket_connection.hpp"

namespace mx {
    class tcp_connection : public rawsocket_connection {
    public:
        explicit tcp_connection(boost::asio::ip::tcp::socket &&socket);

        ~tcp_connection() override;

        void async_read(void *data, size_t length, const read_handler &handler) override {
            boost::asio::async_read(m_socket, boost::asio::buffer(data, length), handler);
        }

        void write(const void *data, size_t length, boost::system::error_code &error_code) override {
            boost::asio::write(m_socket, boost::asio::buffer(data, length), error_code);
        }

    private:
        boost::asio::ip::tcp::socket m_socket;
    };

    tcp_connection::tcp_connection(boost::asio::ip::tcp::socket &&socket)
            : rawsocket_connection(), m_socket(std::move(socket)) {
        m_socket.set_option(boost::asio::ip::tcp::no_delay(true));
    }

    tcp_connection::~tcp_connection() {
        if (m_socket.is_open()) {
            m_socket.close();
        }
    }

}

#endif //MX_TCP_CONNECTION_HPP
