
# google libs
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/glog)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/gflags)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/soil)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/assimp)

# include headers
include_directories(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)
include_directories(${CMAKE_SOURCE_DIR}/third_party/soil/inc)



