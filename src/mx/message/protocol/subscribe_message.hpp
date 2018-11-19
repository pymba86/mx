
#ifndef MX_SUBSCRIBE_MESSAGE_HPP
#define MX_SUBSCRIBE_MESSAGE_HPP

#include <mx/message/message.hpp>
#include <mx/utility/types.hpp>
#include <mx/message/defaults.hpp>

namespace mx {

    /**
     * [SUBSCRIBE, Request|id, Options|dict, Topic|uri]
     */
    class subscribe_message : public message {

    public:
        subscribe_message();

        explicit subscribe_message(msgpack::zone &&zone);

        ~subscribe_message() override;

        message_type get_type() const override;

        std::vector<msgpack::object> marshal() const override;

        void unmarshal(const std::vector<msgpack::object> &fields, msgpack::zone &&zone) override;

        request_id get_request_id() const;

        const msgpack::object &get_options() const;

        std::string get_topic() const;

        void set_request_id(const request_id &request_id);

        void set_options(const msgpack::object &options);

        void set_topic(const std::string_view &topic);

    private:
        msgpack::object m_type;
        msgpack::object m_request_id;
        msgpack::object m_options;
        msgpack::object m_topic;

        static const size_t NUM_FIELDS = 4;

    };

    inline subscribe_message::subscribe_message() : subscribe_message(msgpack::zone()) {
    }

    inline subscribe_message::subscribe_message(msgpack::zone &&zone)
            : message(std::move(zone)),
              m_type(message_type::SUBSCRIBE),
              m_request_id(),
              m_options(msgpack_empty_map()),
              m_topic() {

    }

    inline subscribe_message::~subscribe_message() {

    }

    inline message_type subscribe_message::get_type() const {
        return m_type.as<message_type>();
    }

    inline std::vector<msgpack::object> subscribe_message::marshal() const {
        std::vector<msgpack::object> fields { m_type, m_request_id, m_options, m_topic };
        return fields;
    }

    inline void subscribe_message::unmarshal(const std::vector<msgpack::object> &fields, msgpack::zone &&zone) {
        if (fields.size() != NUM_FIELDS) {
            throw std::invalid_argument("invalid number of fields");
        }

        if (fields[0].as<message_type>() != get_type()) {
            throw std::invalid_argument("invalid message type");
        }

        acquire_zone(std::move(zone));
        m_request_id = fields[1];
        m_options = fields[2];
        m_topic = fields[3];

    }

    inline request_id subscribe_message::get_request_id() const {
        return m_request_id.as<request_id>();
    }

    inline const msgpack::object &subscribe_message::get_options() const {
        return m_options;
    }

    inline    std::string subscribe_message::get_topic() const {
        return m_topic.as<std::string>();
    }

    inline void subscribe_message::set_request_id(const request_id &request_id) {
        m_request_id = msgpack::object(request_id);
    }

    inline void subscribe_message::set_options(const msgpack::object &options) {
        if (options.type == msgpack::type::MAP) {
            m_options = msgpack::object(options, get_zone());
        } else {
            throw std::invalid_argument("invalid options");
        }
    }

    inline void subscribe_message::set_topic(const std::string_view &topic) {
        m_topic = msgpack::object(topic, get_zone());
    }


    inline std::ostream &operator<<(std::ostream &os, const subscribe_message &message) {
        os << "subscribe [" << message.get_request_id() << ", "
           << message.get_options() << ", "
           << message.get_topic() << "]";
        return os;
    }

}

#endif //MX_SUBSCRIBE_MESSAGE_HPP
