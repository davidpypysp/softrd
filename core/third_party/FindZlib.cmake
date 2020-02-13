add_library(zlib_lib STATIC IMPORTED)
set_target_properties(zlib_lib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_MODULE_PATH}/zlib/lib/libz.a"
)