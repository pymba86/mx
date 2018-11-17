
set(SOURCES mx/broker/broker.cpp mx/utility/types.hpp mx/broker/broker.hpp
        mx/session/session.hpp)
set(PUBLIC_HEADERS mx/broker/broker.hpp)
set(PRIVATE_HEADERS  mx/process/process.hpp mx/common/connection_base.hpp mx/process/process.cpp mx/message/protocol/publish_message.hpp mx/message/defaults.hpp mx/message/protocol/subscribe_message.hpp mx/identifiers/generator.hpp mx/broker/broker_subscriptions.hpp mx/trace/trace.hpp mx/trace/trace.cpp mx/message/protocol/event_message.hpp mx/router/router_impl.cpp mx/identifiers/generator.cpp mx/rawsocket/rawsocket_server.hpp mx/router/router_impl.hpp mx/router/router.cpp)




add_library(mx STATIC ${SOURCES} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})

target_link_libraries(mx)
