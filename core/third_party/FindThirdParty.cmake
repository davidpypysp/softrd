
# google libs
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/glog)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/gflags)


add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/soil)
include_directories(${CMAKE_SOURCE_DIR}/third_party/soil/inc)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/assimp)

