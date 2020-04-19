find_library(SOIL_LIB SOIL)
message("soil found: " ${SOIL_LIB})

find_library(ASSIMP_LIB assimp)
message("assimp found: " ${ASSIMP_LIB})

find_library(SDL2_LIB SDL2)
message("sdl2 found: " ${SDL2_LIB}) 

find_library(SDL2_TTF_LIB SDL2_ttf)
message("sdl2_ttf found: " ${SDL2_TTF_LIB})

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/soil)

