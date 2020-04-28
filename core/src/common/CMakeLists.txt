add_library(texture texture.cc)
target_link_libraries(texture math soil GL glog::glog)

add_gtest_exe(texture_test texture_test.cc)
target_link_libraries(texture_test texture gtest stdc++fs)


add_library(common model.cc)
target_link_libraries(common math texture assimp)