add_library (SoftrdAPI SHARED renderer_api.cc)
target_link_libraries(SoftrdAPI renderer)
target_include_directories(SoftrdAPI INTERFACE ${CMAKE_SOURCE_DIR}/src/interface)
