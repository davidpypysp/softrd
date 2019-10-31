add_library(assimp_lib SHARED IMPORTED)
set_target_properties(assimp_lib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_MODULE_PATH}/assimp/lib/libassimp.so"
)
