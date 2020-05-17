cmake_minimum_required (VERSION 3.16)

project(SoftrdCore)

include_directories(${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/wasm_libs/SOIL-wasm/include)
include_directories(${CMAKE_SOURCE_DIR}/wasm_libs/assimp-wasm/assimp-es-dyn/include)


file(GLOB SRC_CC
    src/interface/renderer_api.cc
    src/common/model.cc src/common/texture.cc
    src/modules/*.cc
    src/renderer/*.cc
    src/scene/camera.cc
)


add_library(SoftrdAPIStatic ${SRC_CC})

# target_link_libraries(SoftrdAPIStatic ${assimp_LIBRARIES} soil_libs)