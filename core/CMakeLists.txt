cmake_minimum_required (VERSION 2.6)


project (Softrd)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(third_party)

add_subdirectory(src)
