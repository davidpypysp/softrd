cmake_minimum_required (VERSION 3.16)

# if(WIN32)
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
# else()
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")
# endif(WIN32)

project(SoftrdCore)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")
endif (MSVC)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/third_party)

include_directories(${CMAKE_SOURCE_DIR})
include(CTest)

add_library(SoftrdCore)

if(EMSCRIPTEN) 
    find_package(ThirdPartyWASM)

    add_subdirectory(src)

    target_link_libraries(SoftrdCore soil::soil assimp::assimp)

    set(PORT_EMSC_DIR ${CMAKE_SOURCE_DIR}/port/emscripten)
    add_executable(softrd_api ${PORT_EMSC_DIR}/embind_renderer_api.cc)
    target_link_libraries(softrd_api SoftrdCore)
    set_target_properties(softrd_api PROPERTIES 
        LINK_FLAGS 
            "--bind \
             --pre-js ${PORT_EMSC_DIR}/pre_file.js \
             --post-js ${PORT_EMSC_DIR}/post_file.js"
    )

    set(SOFTRD_JS_DIR ${CMAKE_SOURCE_DIR}/../frontend/softrd-js/softrd_api)
    set(SOFTRD_JS_NODE_MODULES_DIR ${CMAKE_SOURCE_DIR}/../frontend/node_modules/softrd-js/softrd_api)
    install(
        FILES 
            ${CMAKE_BINARY_DIR}/softrd_api.js
            ${CMAKE_BINARY_DIR}/softrd_api.wasm 
        DESTINATION ${SOFTRD_JS_DIR}
    )
    install(
        FILES 
            ${CMAKE_BINARY_DIR}/softrd_api.js
            ${CMAKE_BINARY_DIR}/softrd_api.wasm 
        DESTINATION ${SOFTRD_JS_NODE_MODULES_DIR}
    )
else()
    # vcpkg build
    find_package(ThirdParty)

    add_subdirectory(src)

    target_link_libraries(SoftrdCore soil_libs ${assimp_LIBRARIES})

    # install process
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../middleware/build-core)

    install(TARGETS SoftrdCore
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
endif(EMSCRIPTEN)
