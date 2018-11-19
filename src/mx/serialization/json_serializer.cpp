//
// Created by pymba86 on 19.11.18.
//

#include <mx/serialization/json_serializer.hpp>
#include "json_serializer.hpp"
#include <msgpack.hpp>

namespace mx {

    json_serializer::json_serializer() {}

    json_serializer::~json_serializer() {

    }

    message *json_serializer::deserialize(const char *buffer, size_t length) const {
        msgpack::object item;
        msgpack::zone zone;

        std::vector<msgpack::object> fields;
        item.convert(fields);
    }

    expandable_buffer json_serializer::serialize(const message &message) const {
        return expandable_buffer(0);
    }

}