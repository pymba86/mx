
#ifndef MX_MSGPACK_SERIALIZER_HPP
#define MX_MSGPACK_SERIALIZER_HPP

#include <mx/serialization/serializer.hpp>
#include "expandable_buffer.hpp"

namespace mx {
    class msgpack_serializer : public serializer {
    public:
        serializer_type get_type() const override {
            return serializer_type::msgpack;
        }

        expandable_buffer serialize(const message &message) const override;

        message *deserialize(const char *buffer, size_t length) const override;

    };
}

#endif //MX_MSGPACK_SERIALIZER_HPP
