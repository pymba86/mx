#ifndef MX_GENERATOR_HPP
#define MX_GENERATOR_HPP

#include <cstdint>
#include <stdexcept>
#include <mutex>

namespace mx {


    class generator {
    public:
        generator();

        explicit generator(uint64_t range_start, uint64_t range_end);

        generator(generator const &) = delete;

        generator &operator=(generator const &) = delete;

        uint64_t generate();

    private:
        const uint64_t m_range_start;
        const uint64_t m_range_end;
        uint64_t m_next_id;
    };

    inline generator::generator(uint64_t range_start, uint64_t range_end)
            : m_range_start(range_start),
              m_range_end(range_end),
              m_next_id(range_start) {
        if (m_range_start >= m_range_end) {
            throw std::invalid_argument("range is invalid");
        }
    }

    inline uint64_t generator::generate() {
        if (m_next_id < m_range_start ||
            m_next_id > m_range_end) {
            m_next_id = m_range_start;
        }
        return m_next_id++;
    }

    inline generator::generator() : m_range_start(std::numeric_limits<uint64_t>::min()),
                                           m_range_end(std::numeric_limits<uint64_t>::max())  {

    }

    namespace generator_factory {

        std::shared_ptr<generator> create(const std::string &realm);
    }

}

#endif //MX_GENERATOR_HPP
