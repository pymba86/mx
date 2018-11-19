#include "msgpack_serializer.hpp"

#include <msgpack.hpp>
#include <mx/message/factory.hpp>

namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        bool reference_func(type::object_type type, std::size_t length, void *user_data) {
            // Never copy any STR, BIN or EXT out of the client buffer on parsing,
            // since we create a deep copy of the unpacked item anyway.
            return false;
        }
    }
}

namespace mx {

    expandable_buffer mx::msgpack_serializer::serialize(const message &message) const {
        expandable_buffer buffer(10 * 1024);
        msgpack::packer<expandable_buffer> packer(buffer);
        packer.pack(message.marshal());
        return buffer;
    }

    message *msgpack_serializer::deserialize(const char *buffer, size_t length) const {
        auto item = msgpack::unpack(buffer, length, msgpack::reference_func);
        std::vector<msgpack::object> fields;
        item.get().convert(fields);

        if (fields.empty()) {
            throw std::runtime_error("deserialization failed for message");
        }

        auto type = static_cast<message_type>(fields[0].as<unsigned>());

        std::unique_ptr<message> message(message_factory::create_message(type));

        if (message) {
            message->unmarshal(fields, std::move(*(item.zone())));
        } else {
            throw std::runtime_error("no deserializer defined for message");
        }
        return message.release();
    }
}