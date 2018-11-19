

#include <mx/trace/trace.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <memory>
#include <stdlib.h>
#include <mx/router/manager.hpp>
#include <src/mx/serialization/serializers.hpp>
#include <src/mx/serialization/msgpack_serializer.hpp>
#include <src/mx/rawsocket/rawsocket_server.hpp>
#include <src/mx/rawsocket/tcp_listener.hpp>


int main(int argc, char **argv) {

    mx::trace::set_enabled(true);

    boost::asio::io_service io_service;

    auto manager = std::make_shared<mx::manager>();
    auto router = std::make_shared<mx::router>(io_service, "default");

    manager->add_router(router);

    auto serializers = std::make_shared<mx::serializers>();
    serializers->add_serializer(std::make_shared<mx::msgpack_serializer>());

    auto server = std::make_shared<mx::rawsocket_server>(manager, serializers);

    auto tcp_listener = std::make_shared<mx::tcp_listener>(io_service,
                                                           boost::asio::ip::address(), 8888);

    server->attach_listener(tcp_listener);

    server->start();

    io_service.run();
    return 0;

}