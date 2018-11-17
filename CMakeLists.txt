cmake_minimum_required(VERSION 3.9)
project(mx)

set(PROJECT ${PROJECT_NAME})
string(TOLOWER "${PROJECT}" PROJECT_LC)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(BOOST_ROOT /opt/boost)

find_package(Boost REQUIRED COMPONENTS program_options system thread random)
find_package(Websocketpp REQUIRED)
find_package(Msgpack REQUIRED)

MESSAGE( STATUS "CMAKE_ROOT:               " ${CMAKE_ROOT} )
MESSAGE( STATUS "CMAKE_INSTALL_PREFIX:     " ${CMAKE_INSTALL_PREFIX} )
MESSAGE( STATUS "Boost_INCLUDE_DIRS:       " ${Boost_INCLUDE_DIRS} )
MESSAGE( STATUS "Boost_LIBRARIES:          " ${Boost_LIBRARIES} )
MESSAGE( STATUS "Msgpack_INCLUDE_DIRS:     " ${Msgpack_INCLUDE_DIRS} )
MESSAGE( STATUS "Msgpack_LIBRARIES:        " ${Msgpack_LIBRARIES} )
MESSAGE( STATUS "Websocketpp_INCLUDE_DIRS: " ${Websocketpp_INCLUDE_DIRS} )
MESSAGE( STATUS "Websocketpp_LIBRARIES:    " ${Websocketpp_LIBRARIES} )
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR:    " ${CMAKE_CURRENT_SOURCE_DIR} )

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        ${Websocketpp_INCLUDE_DIRS}
        ${Msgpack_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(src)