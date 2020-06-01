include_directories(${CMAKE_CURRENT_LIST_DIR}/wasm/soil/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/wasm/assimp/include)

set(SOIL_LIB ${CMAKE_SOURCE_DIR}/third_party/wasm/soil/lib/libSOIL.bc)

set(GTest_DIR ${CMAKE_CURRENT_LIST_DIR}/wasm/googletest/lib/cmake/GTest)
find_package(GTest CONFIG REQUIRED
    PATHS ${CMAKE_CURRENT_LIST_DIR}/wasm/googletest/lib/cmake/GTest
)