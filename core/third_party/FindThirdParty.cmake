# find_library(SOIL_LIB SOIL)
# find_library(ASSIMP_LIB assimp)
find_library(SDL2_LIB SDL2)
find_library(SD2_LTTF_LIB SDL2_ttf)

# google libs
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/soil)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/assimp)

