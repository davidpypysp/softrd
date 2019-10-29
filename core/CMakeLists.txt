cmake_minimum_required (VERSION 2.6)


project (Softrd)

message(WARNING "srcdir: " ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(third_party)
