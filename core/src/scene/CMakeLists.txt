target_sources(SoftrdCore PRIVATE 
    camera.cc
)

add_gtest_exe(
    NAME camera_test 
    SRCS camera_test.cc camera.cc
)


