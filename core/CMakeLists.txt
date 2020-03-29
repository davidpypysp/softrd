cmake_minimum_required (VERSION 2.6)


project (Softrd)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/third_party)

include_directories(${CMAKE_SOURCE_DIR})

find_package(ThirdParty)

add_subdirectory(src)
