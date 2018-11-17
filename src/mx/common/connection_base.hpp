#ifndef MX_CONNECTION_BASE_HPP
#define MX_CONNECTION_BASE_HPP

#include <string>
#include <mx/utility/types.hpp>

namespace mx {

    class connection_base {
    public:
        bool has_realm() const;
        void set_realm(const std::string& realm);
        const std::string& get_realm() const;

        bool has_session_id() const;
        void set_session_id(const session_id& session_id);
        const session_id& get_session_id() const;

        void clear_data();

    private:
        std::string m_realm;
        session_id m_session_id;
    };
}

#endif //MX_CONNECTION_BASE_HPP
