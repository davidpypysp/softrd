add_subdirectory(components)
add_subdirectory(modules)
add_subdirectory(renderer)
add_subdirectory(interface)
add_subdirectory(devices)


add_executable(test_api test_api.cc)
target_link_libraries(test_api SoftrdAPI gtest pthread)


add_library (custom_renderer renderer.cc)
target_link_libraries(custom_renderer modules)
target_link_libraries(custom_renderer devices)

add_executable(main main.cc)
target_link_libraries(main custom_renderer)
