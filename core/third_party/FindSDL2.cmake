add_library(sdl2_lib STATIC IMPORTED)
set_target_properties(sdl2_lib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_MODULE_PATH}/sdl2/lib/libSDL2.a"
)

add_library(sdl2_ttf_lib STATIC IMPORTED)
set_target_properties(sdl2_ttf_lib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_MODULE_PATH}/sdl2/lib/libSDL2_ttf.a"
)