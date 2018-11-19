#ifndef MX_SERIALIZER_HPP
#define MX_SERIALIZER_HPP

#include <mx/serialization/type.hpp>
#include <mx/utility/types.hpp>
#include <mx/message/message.hpp>
#include "expandable_buffer.hpp"

namespace mx {
    class serializer {
    public:
        serializer() = default;
        ~serializer() = default;

        virtual serializer_type get_type() const = 0;
        virtual expandable_buffer serialize(const message& message) const = 0;
        virtual message* deserialize(const char* buffer, size_t length) const = 0;
    };
}

#endif //MX_SERIALIZER_HPP
