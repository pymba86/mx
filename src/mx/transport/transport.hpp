//
// Created by pymba86 on 17.11.18.
//

#ifndef MX_TRANSPORT_HPP
#define MX_TRANSPORT_HPP

#include <mx/message/message.hpp>

namespace mx {
    class transport {
        virtual ~transport() = default;
        virtual bool send_message(message&& message) = 0;
    };
}

#endif //MX_TRANSPORT_HPP
