#ifndef MX_FACTORY_HPP
#define MX_FACTORY_HPP

#include <mx/message/message.hpp>
#include <mx/message/protocol/publish_message.hpp>
#include <mx/message/protocol/subscribe_message.hpp>

namespace mx {
    namespace message_factory {
        message* create_message(message_type type) {
            message* message = nullptr;

            switch (type) {
                case message_type::PUBLISH:
                    message = new publish_message();
                    break;
                case message_type::SUBSCRIBE:
                    message = new subscribe_message();
                    break;
            }

            return message;
        }
    }
}

#endif //MX_FACTORY_HPP
