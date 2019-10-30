find_library(ASSIMP_LIB assimp)
find_library(SOIL_LIB soil)
find_library(GL_LIB GL)

add_library (components model.cc)

target_link_libraries(components "${ASSIMP_LIB}")
target_link_libraries(components "${SOIL_LIB}" "${GL_LIB}")
