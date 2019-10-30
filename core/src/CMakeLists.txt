add_subdirectory(components)
add_subdirectory(modules)
add_subdirectory(renderer)
add_subdirectory(interface)

add_executable(test_api test_api.cc)
target_link_libraries(test_api interface)

