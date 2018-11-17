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

    const char* message_type_to_string(message_type type);

    inline std::ostream& operator<<(std::ostream& os, const message_type& type) {
        os << message_type_to_string(type);
        return os;
    }

}

MSGPACK_ADD_ENUM(mx::message_type);


#endif //MX_TYPE_HPP
