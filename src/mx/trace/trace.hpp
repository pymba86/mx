
#ifndef MX_TRACE_HPP
#define MX_TRACE_HPP

#include <boost/format.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <iostream>
#include <string.h>

namespace mx {
    namespace trace {
        extern bool _enabled;

        inline bool is_enabled() {
            return _enabled;
        }

        inline void set_enabled(bool is_enabled) {
            _enabled = is_enabled;
        }

        inline const char *base_file_name(const char *file_path) {
            const char *file_name = strrchr(file_path, '/');
            return file_name == nullptr ? file_path : file_name + 1;
        }

    } // namespace trace
} // namespace mx

// Macro for facilitating debug trace logging.
#define MX_TRACE(...) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), 1), MX_TRACE_ARGS(__VA_ARGS__), MX_TRACE_NOARGS(BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)))

#define MX_TRACE_NOARGS(fmt) \
    if (MX::trace::is_enabled()) { \
        std::cerr << "[" << MX::trace::base_file_name(__FILE__) << ":" << __LINE__ << "][" << __FUNCTION__ << "] " \
                << boost::format(fmt) << std::endl; \
    }

#define MX_TRACE_ARGS(fmt, ...) \
    if (MX::trace::is_enabled()) { \
        std::cerr << "[" << MX::trace::base_file_name(__FILE__) << ":" << __LINE__ << "][" << __FUNCTION__ << "] " \
                << (boost::format(fmt) % __VA_ARGS__) << std::endl; \
    }

}
}

#endif //MX_TRACE_HPP
