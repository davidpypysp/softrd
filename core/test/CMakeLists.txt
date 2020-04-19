macro(add_gtest_exe exe)
    add_executable(${exe} ${ARGV})
    add_dependencies(${exe} googletest)
    target_link_libraries(${exe} gtest gtest_main pthread)
endmacro()


add_subdirectory(math)
