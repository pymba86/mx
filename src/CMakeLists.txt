
set(SOURCES

        mx/utility/types.hpp
        mx/broker/broker.hpp
        mx/session/session.hpp)

set(PUBLIC_HEADERS
        mx/broker/broker.hpp)

set(PRIVATE_HEADERS
        mx/broker/broker.cpp
        mx/process/process.hpp
        mx/common/connection_base.hpp
        mx/process/process.cpp
        mx/message/protocol/publish_message.hpp
        mx/message/defaults.hpp
        mx/message/protocol/subscribe_message.hpp
        mx/identifiers/generator.hpp
        mx/broker/broker_subscriptions.hpp
        mx/trace/trace.hpp
        mx/trace/trace.cpp
        mx/message/protocol/event_message.hpp
        mx/router/router_impl.cpp
        mx/identifiers/generator.cpp
        mx/rawsocket/rawsocket_server.hpp
        mx/router/router_impl.hpp
        mx/router/router.cpp
        mx/serialization/serializer.hpp
        mx/serialization/type.hpp
        mx/serialization/msgpack_serializer.hpp
        mx/serialization/msgpack_serializer.cpp
        mx/message/factory.hpp
        mx/serialization/serializers.hpp
        mx/rawsocket/rawsocket_listener.hpp
        mx/rawsocket/rawsocket_connection.hpp
        mx/rawsocket/rawsocket_server_impl.hpp
        mx/rawsocket/rawsocket_server.cpp
        mx/rawsocket/rawsocket_server_impl.cpp
        mx/rawsocket/tcp_connection.hpp
        mx/rawsocket/tcp_listener.hpp
        mx/rawsocket/tcp_listener.cpp
        mx/rawsocket/rawsocket_transport.hpp
        mx/serialization/expandable_buffer.hpp
        mx/main.cpp mx/serialization/json_serializer.hpp mx/serialization/json_serializer.cpp)


set(TEST mx/test.cpp)

# add_library(mx STATIC ${SOURCES} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})

add_executable(mx ${PRIVATE_HEADERS})
add_executable(test ${TEST})


target_link_libraries(mx ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
