cmake_minimum_required (VERSION 3.16)

project(SoftrdCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")

include_directories(${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/third_party/wasm/soil/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/wasm/assimp/include)


file(GLOB SRC_CC
    src/interface/renderer_api.cc
    src/common/model.cc src/common/texture.cc
    src/modules/*.cc
    src/renderer/*.cc
    src/scene/camera.cc
)

add_library(SoftrdCore ${SRC_CC})
target_link_libraries(SoftrdCore ${CMAKE_SOURCE_DIR}/third_party/wasm/soil/lib/libSOIL.bc)

add_executable(softrd_api embind/embind_renderer_api.cc)
target_link_libraries(softrd_api SoftrdCore)

install(
    FILES ${CMAKE_BINARY_DIR}/softrd_api.js ${CMAKE_BINARY_DIR}/softrd_api.wasm 
    DESTINATION ${CMAKE_SOURCE_DIR}/../frontend/src/wasm
)