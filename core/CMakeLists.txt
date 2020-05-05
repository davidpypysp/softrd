cmake_minimum_required (VERSION 2.6)
# set(CMAKE_TOOLCHAIN_FILE "C:/Users/david/vcpkg/scripts/buildsystems/vcpkg.cmake")

project (softrd)

if (MSVC)
    message("CMAKE_TOOLCHAIN_FILE: " ${CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif (MSVC)

# install for middleware by default
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../middleware/build-core)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/third_party)
include_directories(${CMAKE_SOURCE_DIR})
include(CTest)

find_package(ThirdParty)

add_subdirectory(src)


install(TARGETS SoftrdAPI
    DESTINATION lib
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/src
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)