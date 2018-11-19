#ifndef MX_SERIALIZERS_HPP
#define MX_SERIALIZERS_HPP

#include <unordered_map>
#include <mx/serialization/type.hpp>
#include <mx/serialization/serializer.hpp>
#include <memory>

namespace mx {
    class serializers {
    public:
        serializers();

        ~serializers() = default;

        bool add_serializer(const std::shared_ptr<serializer> &serializer);

        std::shared_ptr<serializer> get_serializer(const serializer_type &type);

        bool has_serializer(const serializer_type &type) const;

        void remove_serializer(const serializer_type &type);

    private:
        std::unordered_map<serializer_type, std::shared_ptr<serializer>> m_serializers;
    };

    inline    serializers::serializers() : m_serializers() {

    }

    inline bool serializers::add_serializer(const std::shared_ptr<serializer> &serializer) {
        auto result = m_serializers.insert(std::make_pair(serializer->get_type(), serializer));
        return result.second;
    }

    inline std::shared_ptr<serializer> serializers::get_serializer(const serializer_type &type) {
        auto itr = m_serializers.find(type);
        return itr != m_serializers.end() ? itr->second : nullptr;
    }

    inline bool serializers::has_serializer(const serializer_type &type) const {
        return m_serializers.find(type) != m_serializers.end();
    }

    inline void serializers::remove_serializer(const serializer_type &type) {
        m_serializers.erase(type);
    }
}

#endif //MX_SERIALIZERS_HPP
