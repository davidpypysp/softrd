macro(add_gtest_exe exe)
    add_executable(${exe} ${ARGV})
    target_link_libraries(${exe} gtest pthread)
endmacro()

add_subdirectory(math)
