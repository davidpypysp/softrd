add_library (interface SHARED renderer_api.cc)
link_directories(${CMAKE_SOURCE_DIR}/src/renderer)
target_link_libraries(interface renderer)
find_library(SOIL_LIB soil)
