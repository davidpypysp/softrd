cmake_minimum_required (VERSION 3.16)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
else()
    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif(WIN32)

project(SoftrdCore)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif (MSVC)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include_directories(${CMAKE_SOURCE_DIR})
include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
find_package(ThirdParty)

add_subdirectory(src)

# install process
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../middleware/build-core)

install(TARGETS SoftrdAPI
    DESTINATION lib
)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/src
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)

# generate config cmake
include(CMakePackageConfigHelpers)
set(VCPKG_INCLUDE_DIR ${_VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/include)
configure_package_config_file(
  ${CMAKE_SOURCE_DIR}/SoftrdCoreConfig.cmake.in
  "SoftrdCoreConfig.cmake"
  INSTALL_DESTINATION .
  PATH_VARS VCPKG_INCLUDE_DIR 
)
install(FILES ${CMAKE_BINARY_DIR}/SoftrdCoreConfig.cmake DESTINATION . )