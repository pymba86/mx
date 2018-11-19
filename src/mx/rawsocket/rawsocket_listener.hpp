
#ifndef MX_RAWSOCKET_LISTENER_HPP
#define MX_RAWSOCKET_LISTENER_HPP


#include <functional>
#include <boost/asio/io_service.hpp>
#include <mx/trace/trace.hpp>

namespace mx {

    class rawsocket_connection;

    class rawsocket_listener {
    public:
        using error_handler = std::function<void(rawsocket_listener &listener,
                                                 const boost::system::error_code &error_code)>;

        using accept_hanlder = std::function<void(const std::shared_ptr<rawsocket_connection> &)>;

    public:
        rawsocket_listener();

        virtual ~rawsocket_listener() = default;

        virtual void start_listening() = 0;

        virtual void stop_listening() = 0;

        virtual std::shared_ptr<rawsocket_connection> create_connection() = 0;

        bool is_listening() const;

        const error_handler &get_error_handler() const;

        void set_error_handler(const error_handler &handler);

        const accept_hanlder &get_accept_handler() const;

        void set_accept_handler(const accept_hanlder &handler);

        void handle_accept(const boost::system::error_code &error_code);

    protected:
        virtual void async_accept() = 0;

        void set_listening(bool is_listening);

    private:
        bool m_listening;
        error_handler m_error_handler;
        accept_hanlder m_accept_handler;

    };

    inline rawsocket_listener::rawsocket_listener()
            : m_listening(false),
              m_accept_handler(),
              m_error_handler() {

    }

    inline  bool rawsocket_listener::is_listening() const {
        return m_listening;
    }

    inline const rawsocket_listener::error_handler &rawsocket_listener::get_error_handler() const {
        return m_error_handler;
    }

    inline  void rawsocket_listener::set_error_handler(const rawsocket_listener::error_handler &handler) {
        m_error_handler = handler;
    }

    inline const rawsocket_listener::accept_hanlder &rawsocket_listener::get_accept_handler() const {
        return m_accept_handler;
    }

    inline void rawsocket_listener::set_accept_handler(const rawsocket_listener::accept_hanlder &handler) {
        m_accept_handler = handler;
    }

    inline  void rawsocket_listener::handle_accept(const boost::system::error_code &error_code) {
        if (error_code) {
            assert(get_error_handler());
            const auto& error_hanlder = get_error_handler();
            error_hanlder(*this,error_code);
            return;
        }

        assert(get_accept_handler());
        const auto& accept_handler = get_accept_handler();
        accept_handler(create_connection());
        async_accept();
    }

    inline void rawsocket_listener::set_listening(bool is_listening) {
        m_listening = is_listening;
    }
}

#endif //MX_RAWSOCKET_LISTENER_HPP
