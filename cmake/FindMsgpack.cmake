# - Try to find msgpack
# Once done this will define
#  Msgpack_FOUND - System has msgpack
#  Msgpack_INCLUDE_DIRS - The msgpack include directories

set(MSGPACK_ROOT /opt/msgpack)
set(Msgpack_FOUND TRUE)
set(Msgpack_INCLUDE_DIRS "${MSGPACK_ROOT}/include")
set(Msgpack_LIBRARIES "${MSGPACK_ROOT}/lib")


