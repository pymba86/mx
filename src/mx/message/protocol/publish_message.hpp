#ifndef MX_PUBLISH_MESSAGE_HPP
#define MX_PUBLISH_MESSAGE_HPP

#include <mx/message/message.hpp>
#include <mx/utility/types.hpp>
#include <mx/message/defaults.hpp>

namespace mx {

    /**
     * [PUBLISH, Request|id, Options|dict, Topic|uri]
     * [PUBLISH, Request|id, Options|dict, Topic|uri, Arguments|list]
     * [PUBLISH, Request|id, Options|dict, Topic|uri, Arguments|list, ArgumentsKw|dict]
     * */
    class publish_message : message {

    public:
        publish_message();

        explicit publish_message(msgpack::zone &&zone);

        ~publish_message() override;

        message_type get_type() const override;

        std::vector<msgpack::object> marshal() const override;

        void unmarshal(const std::vector<msgpack::object> &fields, msgpack::zone &&zone) override;

        request_id get_request_id() const;

        const msgpack::object &get_options() const;

        std::string get_topic() const;

        const msgpack::object &get_arguments() const;

        const msgpack::object &get_arguments_kw() const;

        void set_request_id(const request_id &request_id);

        void set_options(const msgpack::object &options);

        void set_topic(const std::string_view &topic);

        void set_arguments(const msgpack::object &arguments);

        void set_arguments_kw(const msgpack::object &arguments_kw);

    private:
        msgpack::object m_type;
        msgpack::object m_request_id;
        msgpack::object m_options;
        msgpack::object m_topic;
        msgpack::object m_arguments;
        msgpack::object m_arguments_kw;

        static const size_t MIN_FIELDS = 4;
        static const size_t MAX_FIELDS = 6;

    };

    inline publish_message::publish_message() : publish_message(msgpack::zone()) {
    }

    inline publish_message::publish_message(msgpack::zone &&zone)
            : message(std::move(zone)),
              m_type(message_type::PUBLISH),
              m_request_id(),
              m_options(msgpack_empty_map()),
              m_topic(),
              m_arguments(),
              m_arguments_kw() {

    }

    inline publish_message::~publish_message() {

    }

    inline message_type publish_message::get_type() const {
        return m_type.as<message_type>();
    }

    inline std::vector<msgpack::object> publish_message::marshal() const {
        std::vector<msgpack::object> fields;

        if (!m_arguments_kw.is_nil()) {
            if (!m_arguments.is_nil()) {
                fields = {m_type, m_request_id, m_options, m_topic, m_arguments, m_arguments_kw};
            } else {
                fields = {m_type, m_request_id, m_options, m_topic, msgpack_empty_map(), m_arguments_kw};
            }
        } else if (!m_arguments.is_nil()) {
            fields = {m_type, m_request_id, m_options, m_topic, m_arguments};
        } else {
            fields = {m_type, m_request_id, m_options, m_topic};
        }

        return fields;
    }

    inline void publish_message::unmarshal(const std::vector<msgpack::object> &fields, msgpack::zone &&zone) {
        if (fields.size() < MIN_FIELDS || fields.size() > MAX_FIELDS) {
            throw std::invalid_argument("invalid number of fields");
        }

        if (fields[0].as<message_type>() != get_type()) {
            throw std::invalid_argument("invalid message type");
        }

        acquire_zone(std::move(zone));
        m_request_id = fields[1];
        m_options = fields[2];
        m_topic = fields[3];

        if (fields.size() >= 5) {
            m_arguments = fields[4];
        }
        if (fields.size() == 6) {
            m_arguments_kw = fields[5];
        }

    }

    inline request_id publish_message::get_request_id() const {
        return m_request_id.as<request_id>();
    }

    inline const msgpack::object &publish_message::get_options() const {
        return m_options;
    }

    std::string publish_message::get_topic() const {
        return m_topic.as<std::string>();
    }

    const msgpack::object &publish_message::get_arguments() const {
        return m_arguments;
    }

    const msgpack::object &publish_message::get_arguments_kw() const {
        return m_arguments_kw;
    }

    inline void publish_message::set_request_id(const request_id &request_id) {
        m_request_id = msgpack::object(request_id);
    }

    inline void publish_message::set_options(const msgpack::object &options) {
        if (options.type == msgpack::type::MAP) {
            m_options = msgpack::object(options, get_zone());
        } else {
            throw std::invalid_argument("invalid options");
        }
    }

    inline void publish_message::set_topic(const std::string_view &topic) {
        m_topic = msgpack::object(topic, get_zone());
    }

    inline void publish_message::set_arguments(const msgpack::object &arguments) {
        if (arguments.type == msgpack::type::NIL || arguments.type == msgpack::type::ARRAY) {
            m_arguments = msgpack::object(arguments, get_zone());
        } else {
            throw std::invalid_argument("invalid arguments");
        }
    }

    inline void publish_message::set_arguments_kw(const msgpack::object &arguments_kw) {
        if (arguments_kw.type == msgpack::type::NIL || arguments_kw.type == msgpack::type::ARRAY) {
            m_arguments_kw = msgpack::object(arguments_kw, get_zone());
        } else {
            throw std::invalid_argument("invalid arguments_kw");
        }
    }

    inline std::ostream &operator<<(std::ostream &os, const publish_message &message) {
        os << "publish [" << message.get_request_id() << ", "
           << message.get_options() << ", "
           << message.get_topic() << ", "
           << message.get_arguments() << ", "
           << message.get_arguments_kw() << "]";
        return os;
    }

}

#endif //MX_PUBLISH_MESSAGE_HPP