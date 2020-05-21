cmake_minimum_required (VERSION 3.16)

project(SoftrdCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")

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


add_library(SoftrdCore ${SRC_CC})
target_link_libraries(SoftrdCore ${CMAKE_SOURCE_DIR}/wasm_libs/SOIL-wasm/libSOIL.bc)
# set_target_properties(SoftrdCore PROPERTIES COMPILE_FLAGS
#      "--preload-file ${CMAKE_BINARY_DIR}/something.jpg"
# )


add_executable(softrd_api embind/embind_renderer_api.cc)
target_link_libraries(softrd_api SoftrdCore)
# target_compile_options(softrd_api PUBLIC "${CMAKE_CXX_FLAGS} --bind")

## build emscripten
# em++ --bind  ..\embind\embind_renderer_api.cc -I../ -I..\wasm_libs\assimp-wasm\assimp-es-dyn\include\ -I..\wasm_libs\SOIL-wasm\include\ -lSoftrdAPIStatic -L. -o embind_renderer_api.js