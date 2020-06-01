target_sources(SoftrdCore PRIVATE 
    texture.cc 
    model.cc
)

add_gtest_exe(texture_test texture_test.cc texture.cc)
target_link_libraries(texture_test ${SOIL_LIB})
