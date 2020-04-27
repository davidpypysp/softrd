macro(add_gtest_exe exe)
    add_executable(${exe} ${ARGV})
    target_link_libraries(${exe} gtest pthread)
    add_test(NAME ${exe} COMMAND ${exe})
endmacro()

add_subdirectory(common)
add_subdirectory(modules)
add_subdirectory(renderer)
add_subdirectory(interface)
add_subdirectory(devices)
add_subdirectory(math)
add_subdirectory(scene)

add_library (custom_renderer renderer.cc)
target_link_libraries(custom_renderer modules devices)

add_executable(main main.cc)
target_link_libraries(main custom_renderer)

add_executable(test_api test_api.cc)
target_link_libraries(test_api SoftrdAPI gtest pthread)