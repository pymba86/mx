//
// Created by pymba86 on 17.11.18.
//

#ifndef MX_TYPE_HPP
#define MX_TYPE_HPP

#include <ostream>
#include <type_traits>
#include <msgpack.hpp>

namespace mx {

    enum class message_type : unsigned {
        HELLO = 1,
        WELCOME = 2,
        ABORT = 3,
        CHALLENGE = 4,
        AUTHENTICATE = 5,
        GOODBYE = 6,
        HEARTBEAT = 7,
        ERROR = 8,
        PUBLISH = 16,
        PUBLISHED = 17,
        SUBSCRIBE = 32,
        SUBSCRIBED = 33,
        UNSUBSCRIBE = 34,
        UNSUBSCRIBED = 35,
        EVENT = 36,
        CALL = 48,
        CANCEL = 49,
        RESULT = 50,
        REGISTER = 64,
        REGISTERED = 65,
        UNREGISTER = 66,
        UNREGISTERED = 67,
        INVOCATION = 68,
        INTERRUPT = 69,
        YIELD = 70
    };

   inline const char* message_type_to_string(message_type type) {
        const char* str = nullptr;

        switch(type)
        {
            case message_type::HELLO:
                str = "hello";
                break;
            case message_type::WELCOME:
                str = "welcome";
                break;
            case message_type::ABORT:
                str = "abort";
                break;
            case message_type::CHALLENGE:
                str = "challenge";
                break;
            case message_type::AUTHENTICATE:
                str = "authenticate";
                break;
            case message_type::GOODBYE:
                str = "goodbye";
                break;
            case message_type::HEARTBEAT:
                str = "heartbeat";
                break;
            case message_type::ERROR:
                str = "error";
                break;
            case message_type::PUBLISH:
                str = "publish";
                break;
            case message_type::PUBLISHED:
                str = "published";
                break;
            case message_type::SUBSCRIBE:
                str = "subscribe";
                break;
            case message_type::SUBSCRIBED:
                str = "subscribed";
                break;
            case message_type::UNSUBSCRIBE:
                str = "unsubscribe";
                break;
            case message_type::UNSUBSCRIBED:
                str = "unsubscribed";
                break;
            case message_type::EVENT:
                str = "event";
                break;
            case message_type::CALL:
                str = "call";
                break;
            case message_type::CANCEL:
                str = "cancel";
                break;
            case message_type::RESULT:
                str = "result";
                break;
            case message_type::REGISTER:
                str = "register";
                break;
            case message_type::REGISTERED:
                str = "registered";
                break;
            case message_type::UNREGISTER:
                str = "unregister";
                break;
            case message_type::UNREGISTERED:
                str = "unregistered";
                break;
            case message_type::INVOCATION:
                str = "invocation";
                break;
            case message_type::INTERRUPT:
                str = "interrupt";
                break;
            case message_type::YIELD:
                str = "yield";
                break;
            default:
                throw std::invalid_argument("unknown message type");
                break;
        }
    }

    inline std::ostream& operator<<(std::ostream& os, const message_type& type) {
        os << message_type_to_string(type);
        return os;
    }

}

MSGPACK_ADD_ENUM(mx::message_type);


#endif //MX_TYPE_HPP
