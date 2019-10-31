find_library(ASSIMP_LIB assimp)
find_library(SOIL_LIB soil)
find_library(GL_LIB GL)

add_library (components model.cc)

add_library(soil_lib UNKNOWN IMPORTED)
set_target_properties(soil_lib PROPERTIES
    IMPORTED_LOCATION "${SOIL_LIB}"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${GL_LIB}"
)

add_library(assimp_lib UNKNOWN IMPORTED)
set_target_properties(assimp_lib PROPERTIES
    IMPORTED_LOCATION "${ASSIMP_LIB}"
)


target_link_libraries(components assimp_lib)
target_link_libraries(components soil_lib)
