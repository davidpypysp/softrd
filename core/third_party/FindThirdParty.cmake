

# # abseil
# find_package(absl CONFIG REQUIRED)

# # google test
# find_package(GTest CONFIG REQUIRED)

# # glog
# find_package(glog CONFIG REQUIRED)

# soil
find_package(SOIL CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
add_library(soil_libs INTERFACE)
target_link_libraries(soil_libs INTERFACE SOIL ${OPENGL_LIBRARY})
if(APPLE)
  target_link_libraries(soil_libs INTERFACE "-framework Foundation")
endif(APPLE)

## assimp
find_package(assimp CONFIG REQUIRED)