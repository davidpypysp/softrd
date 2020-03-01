add_library (devices device.cc)

target_link_libraries(devices ${SDL2_LIB} ${SDL2_TTF_LIB})
