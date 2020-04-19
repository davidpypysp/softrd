macro(add_gtest_exe exe)
    add_executable(${exe} ${ARGV})
    target_link_libraries(${exe} ${GTEST_LIB} pthread)
endmacro()


add_subdirectory(math)
