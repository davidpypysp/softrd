add_library(texture texture.cc)
target_link_libraries(texture math soil_libs glog::glog)

add_gtest_exe(texture_test texture_test.cc)
target_link_libraries(texture_test texture)

add_library(common model.cc)
target_link_libraries(common PRIVATE math texture ${assimp_LIBRARIES})