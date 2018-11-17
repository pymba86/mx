#ifndef MX_TYPES_HPP
#define MX_TYPES_HPP

#include <cstdint>
#include <vector>

namespace mx {
    using session_id = uint64_t;
    using request_id = uint64_t;
    using subscription_id = uint64_t;
    using buffer_t = std::vector<char>;
}

#endif //MX_TYPES_HPP
