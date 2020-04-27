add_library(camera camera.cc)
target_link_libraries(camera math)

add_gtest_exe(camera_test camera_test.cc)
target_link_libraries(camera_test camera glog::glog)