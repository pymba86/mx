//
// Created by pymba86 on 17.11.18.
//

#ifndef MX_DEFAULS_HPP
#define MX_DEFAULS_HPP

#include <map>
#include <msgpack.hpp>

namespace mx {
    namespace {
        msgpack::zone zone;
        const std::map<int,int> EMPTY_MAP;
        const msgpack::object MSGPACK_EMPTY_MAP(EMPTY_MAP, zone);
    } // namespace

    inline const msgpack::object& msgpack_empty_map()
    {
        return MSGPACK_EMPTY_MAP;
    }

}

#endif //MX_DEFAULS_HPP
