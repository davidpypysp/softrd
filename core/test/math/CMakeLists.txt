add_executable(vector_test vector_test.cc)
target_link_libraries(vector_test ${GTEST_LIB} pthread)