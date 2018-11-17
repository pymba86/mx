#ifndef MX_PROCESS_HPP
#define MX_PROCESS_HPP

#include <bits/unique_ptr.h>
#include <mx/transport/transport.hpp>
#include <mx/common/connection_base.hpp>

namespace mx {

    class manager;

    class process {
        explicit process(std::shared_ptr<manager> manager);

        void process_message(const std::unique_ptr<message> &message,
                             std::unique_ptr<transport> &&transport,
                             connection_base *connection_base);

    private:
        std::shared_ptr<manager> m_manager;

    };

    inline process::process(std::shared_ptr<manager> manager) : m_manager(std::move(manager)) {

    }
}

#endif //MX_PROCESS_HPP
