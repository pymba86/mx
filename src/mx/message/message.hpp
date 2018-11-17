#ifndef MX_MESSAGE_HPP
#define MX_MESSAGE_HPP

#include <msgpack.hpp>
#include "type.hpp"

namespace mx {
    class message {
    public:
        message();
        explicit message(msgpack::zone&& zone);
        virtual ~message() = default;

        message(const message&) = delete;
        message(message&&) = delete;

        message&operator=(message const&) = delete;
        message&operator=(message&&) = delete;

        msgpack::zone release_zone();
        msgpack::zone& get_zone();

        virtual message_type get_type() const = 0;
        virtual std::vector<msgpack::object> marshal() const = 0;
        virtual void unmarshal(const std::vector<msgpack::object>& fields, msgpack::zone&& zone) = 0;

    protected:
        void acquire_zone(msgpack::zone&& zone);

    private:
        msgpack::zone m_zone;
    };

    inline message::message() : m_zone() {}

    inline message::message(msgpack::zone &&zone) : m_zone(std::move(zone)) {}

    inline msgpack::zone message::release_zone() {
        return std::move(m_zone);
    }

    inline msgpack::zone &message::get_zone() {
        return m_zone;
    }

    inline void message::acquire_zone(msgpack::zone &&zone) {
        m_zone = std::move(zone);
    }
}

#endif //MX_MESSAGE_HPP
