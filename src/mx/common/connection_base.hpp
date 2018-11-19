#ifndef MX_CONNECTION_BASE_HPP
#define MX_CONNECTION_BASE_HPP

#include <string>
#include <mx/utility/types.hpp>

namespace mx {

    class connection_base {
    public:
        connection_base();
        virtual ~connection_base() = default;

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

   inline bool connection_base::has_realm() const {
        return !m_realm.empty();
    }

    inline void connection_base::set_realm(const std::string &realm) {
        m_realm = realm;
    }

    inline connection_base::connection_base() : m_realm(), m_session_id() {

    }

    inline const std::string &connection_base::get_realm() const {
        return m_realm;
    }

    inline bool connection_base::has_session_id() const {
        return m_session_id > 0;
    }

    inline void connection_base::set_session_id(const session_id &session_id) {
        m_session_id = session_id;
    }

    inline const session_id &connection_base::get_session_id() const {
        return m_session_id;
    }

    inline void connection_base::clear_data() {
        m_session_id = session_id();
        m_realm = std::string();
    }
}

#endif //MX_CONNECTION_BASE_HPP
