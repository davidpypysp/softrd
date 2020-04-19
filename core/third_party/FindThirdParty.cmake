include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

find_library(SOIL_LIB SOIL)
message("soil found: " ${SOIL_LIB})

find_library(ASSIMP_LIB assimp)
message("assimp found: " ${ASSIMP_LIB})

find_library(SDL2_LIB SDL2)
message("sdl2 found: " ${SDL2_LIB}) 

find_library(SDL2_TTF_LIB SDL2_ttf)
message("sdl2_ttf found: " ${SDL2_TTF_LIB})

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/abseil)
