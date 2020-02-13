add_library(freetype2_lib STATIC IMPORTED)
set_target_properties(freetype2_lib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_MODULE_PATH}/freetype2/lib/libfreetype.a"
)