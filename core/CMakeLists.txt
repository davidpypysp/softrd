cmake_minimum_required (VERSION 3.16)

project(SoftrdCore)

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


add_library(SoftrdCore)
target_link_libraries(SoftrdCore ${CMAKE_SOURCE_DIR}/third_party/wasm/soil/lib/libSOIL.bc)

add_subdirectory(src)



add_executable(softrd_api embind/embind_renderer_api.cc)
target_link_libraries(softrd_api SoftrdCore)
set_target_properties(softrd_api PROPERTIES 
    LINK_FLAGS "--bind"
)

install(
    FILES ${CMAKE_BINARY_DIR}/softrd_api.wasm 
    DESTINATION ${CMAKE_SOURCE_DIR}/../frontend/src/
) 