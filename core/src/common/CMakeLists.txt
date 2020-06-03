target_sources(SoftrdCore PRIVATE 
    texture.cc 
    model.cc
)

add_gtest_exe(
    NAME texture_test
    SRCS texture_test.cc texture.cc
    DEPS ${SOIL_LIB}
)

