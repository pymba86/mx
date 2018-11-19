#ifndef MX_ROUTER_MANAGER_HPP
#define MX_ROUTER_MANAGER_HPP

#include <bits/shared_ptr.h>
#include <string>
#include "router.hpp"


namespace mx {

    class manager {
    public:
        manager();
        ~manager() = default;

        bool add_router(const std::shared_ptr<router> &router);

        std::shared_ptr<router> get_router(const std::string &realm);

        void remove_router(const std::string &realm);

    private:
        std::unordered_map<std::string, std::shared_ptr<router>> m_routers;
    };

    inline    manager::manager() : m_routers() {}

    inline bool manager::add_router(const std::shared_ptr<router> &router) {

        auto result = m_routers.insert(std::make_pair(router->get_realm(), router));
        return result.second;
    }

    inline std::shared_ptr<router> manager::get_router(const std::string &realm) {
        auto itr = m_routers.find(realm);
        return itr != m_routers.end() ? itr->second : nullptr;
    }

    inline void manager::remove_router(const std::string &realm) {

    };



}

#endif //MX_ROUTER_MANAGER_HPP
