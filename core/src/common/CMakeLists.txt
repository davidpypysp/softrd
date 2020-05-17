add_library(texture texture.cc)
target_link_libraries(texture soil_libs)

# add_gtest_exe(texture_test texture_test.cc)
# target_link_libraries(texture_test texture glog::glog)

add_library(common model.cc)
target_link_libraries(common texture ${assimp_LIBRARIES})