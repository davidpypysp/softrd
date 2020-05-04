
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)

set(BUILD_TESTING OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/glog)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/soil)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/assimp)

find_package(OpenGL REQUIRED)

add_library(soil_libs INTERFACE)
target_link_libraries(soil_libs INTERFACE soil ${OPENGL_LIBRARY})
if(APPLE)
  target_link_libraries(soil_libs INTERFACE "-framework Foundation")
endif()

# include headers
include_directories(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)
include_directories(${CMAKE_SOURCE_DIR}/third_party/soil/inc)



