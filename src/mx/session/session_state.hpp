//
// Created by pymba86 on 16.11.18.
//

#ifndef MX_SESSION_STATE_HPP
#define MX_SESSION_STATE_HPP

#include <cstdint>
#include <ostream>
#include <string>


namespace mx {
    enum class session_state : uint8_t {
        none,
        wait,
        open,
        closing_wait,
        closing,
        closed
    };
}

#endif //MX_SESSION_STATE_HPP
