#ifndef MX_SESSION_HPP
#define MX_SESSION_HPP

#include <map>
#include <mutex>
#include <memory>
#include <future>
#include <set>
#include <utility>

#include "session_state.hpp"
#include <mx/utility/types.hpp>
#include <mx/transport/transport.hpp>

namespace mx {

class session  {
    public:
        session();

        session(const session_id &session_id, std::string realm,
                std::unique_ptr<transport> transport);

        ~session() = default;

        session(session const &) = delete;

        session &operator=(session const &) = delete;

        const std::string &get_realm() const;

        const std::unique_ptr<transport>& get_transport() const;

        session_state get_state() const;

        session_id get_session_id() const;

        void set_state(session_state state);

    private:
       const std::string m_realm;
        session_state m_state;
        session_id m_session_id;
        std::unique_ptr<transport> m_transport;
    };

    inline session::session() : m_realm(), m_session_id(), m_state(session_state::none),
                                m_transport() {}

    inline session::session(const session_id &session_id, std::string realm,
                            std::unique_ptr<transport> transport)
            : m_realm(std::move(realm)),
              m_session_id(session_id),
              m_state(session_state::none),
              m_transport(std::move(transport)) {}

   inline const std::string &session::get_realm() const {
        return m_realm;
    }

   inline const std::unique_ptr<transport>& session::get_transport() const {
        return m_transport;
    }

    inline session_state session::get_state() const {
        return m_state;
    }

    inline session_id session::get_session_id() const {
        return m_session_id;
    }

    void session::set_state(session_state state) {
        m_state = state;
    }


}

#endif //MX_SESSION_HPP
