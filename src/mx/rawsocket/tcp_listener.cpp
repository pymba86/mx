
#include "tcp_listener.hpp"
#include "tcp_connection.hpp"

namespace mx {

    tcp_listener::tcp_listener(boost::asio::io_service &io_service, const boost::asio::ip::address &ip_address,
                               uint16_t port)
            : rawsocket_listener(),
              m_socket(io_service),
              m_acceptor(io_service),
              m_endpoint(ip_address, port) {

    }

    tcp_listener::~tcp_listener() {
        stop_listening();
    }

    void tcp_listener::start_listening() {
        assert(get_error_handler());
        assert(get_accept_handler());

        if (is_listening()) {
            return;
        }

        m_acceptor.open(m_endpoint.protocol());
        m_acceptor.set_option(
                boost::asio::ip::tcp::acceptor::reuse_address(true));
        m_acceptor.bind(m_endpoint);
        m_acceptor.listen();

        set_listening(true);
        async_accept();
    }

    void tcp_listener::stop_listening() {
        if (!is_listening()) {
            return;
        }

        m_acceptor.close();
        set_listening(false);
    }

    std::shared_ptr<rawsocket_connection> tcp_listener::create_connection() {
        return std::make_shared<tcp_connection>(std::move(m_socket));
    }

    void tcp_listener::async_accept() {
        m_acceptor.async_accept(m_socket,
                                std::bind(&rawsocket_listener::handle_accept,
                                          shared_from_this(),
                                          std::placeholders::_1));
    }


}
