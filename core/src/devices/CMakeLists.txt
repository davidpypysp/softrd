# find_package(SDL REQUIRED)
find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_TTF_LIBRARY SDL2_TTF)

message("sdl2 found:" ${SDL_FOUND} ${SDL_DIR})
message("sdl2 lib found:" ${SDL2_LIBRARY}) 
message("sdl2 ttf lib found:" ${SDL2_TTF_LIBRARY})

find_package(Freetype2)
find_package(Zlib)

add_library (devices device.cc)

target_link_libraries(devices ${SDL2_LIBRARY} pthread dl)
# target_link_libraries(devices sdl2_ttf_lib freetype2_lib zlib_lib)
target_link_libraries(devices ${SDL2_TTF_LIBRARY})
