find_package(SDL2)
find_package(Freetype2)
find_package(Zlib)

add_library (devices device.cc)

target_link_libraries(devices sdl2_lib pthread dl)
target_link_libraries(devices sdl2_ttf_lib freetype2_lib zlib_lib)
