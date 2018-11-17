# - Try to find websocketpp
# Once done this will define
#  Websocketpp_FOUND - System has websocketpp
#  Websocketpp_INCLUDE_DIRS - The websocketpp include directories


set(WEBSOCKETPP_ROOT /opt/websocketpp)
set(Websocketpp_FOUND TRUE)
set(Websocketpp_INCLUDE_DIRS "${WEBSOCKETPP_ROOT}/include")
set(Websocketpp_LIBRARIES "${WEBSOCKETPP_ROOT}/lib")

