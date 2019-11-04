set(LIB_DIRS
    ${CMAKE_MODULE_PATH}/assimp
    ${CMAKE_MODULE_PATH}/soil
)

set(CMAKE_PREFIX_PATH ${LIB_DIRS} ${CMAKE_PREFIX_PATH})

message("cmake prefix path: " ${CMAKE_PREFIX_PATH})


find_library(ASSIMP_LIB assimp)
find_library(SOIL_LIB soil)
find_library(GL_LIB GL)


add_library(soil_lib SHARED IMPORTED)
set_target_properties(soil_lib PROPERTIES
    IMPORTED_LOCATION "${SOIL_LIB}"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${GL_LIB}"
)

message("assimplib: " ${ASSIMP_LIB})
message("soillib: " ${SOIL_LIB})
message("gllib: " ${GL_LIB})

add_library(assimp_lib SHARED IMPORTED)
set_target_properties(assimp_lib PROPERTIES
    IMPORTED_LOCATION "${ASSIMP_LIB}"
)
