target_sources(SoftrdCore PRIVATE 
    texture.cc 
    model.cc
)

add_gtest_exe(
    NAME texture_test
    SRCS texture_test.cc texture.cc
    DEPS ${SOIL_LIB}
)

add_gtest_exe(
    NAME model_test
    SRCS model_test.cc model.cc
    DEPS assimp::assimp
)
set_target_properties(model_test PROPERTIES 
    LINK_FLAGS "--preload-file ../../../resource/suzanne"
    SUFFIX ".html"
)
