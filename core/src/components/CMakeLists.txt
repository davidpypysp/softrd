# find_package(Assimp)
# find_package(Soil)

find_library(SOIL_LIBRARY SOIL)
message("soil found:" ${SOIL_LIBRARY})

find_library(ASSIMP_LIBRARY assimp)
message("assimp found:" ${ASSIMP_LIBRARY})
add_library (components model.cc)

target_link_libraries(components ${ASSIMP_LIBRARY})
target_link_libraries(components ${SOIL_LIBRARY})
