
#ifndef MX_JSON_SERIALIZER_HPP
#define MX_JSON_SERIALIZER_HPP

#include <mx/serialization/serializer.hpp>
#include <mx/serialization/type.hpp>

namespace mx {
    class json_serializer : public serializer
    {
    public:
        json_serializer();

        ~json_serializer();

        serializer_type get_type() const override;

        message* deserialize(const char* buffer, size_t length) const override;

        expandable_buffer serialize(const message& message) const override;
    };


    inline serializer_type json_serializer::get_type() const
    {
        return serializer_type::json;
    }

}

#endif //MX_JSON_SERIALIZER_HPP
