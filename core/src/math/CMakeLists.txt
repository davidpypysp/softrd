add_library(math INTERFACE)
target_include_directories(math INTERFACE ./)
target_link_libraries(math INTERFACE absl::str_format_internal)

add_gtest_exe(vector_test vector_test.cc)
target_link_libraries(vector_test math glog::glog)
add_test(NAME vector_test COMMAND vector_test)
