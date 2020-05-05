
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest)

set(BUILD_TESTING OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/abseil-cpp)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp/absl
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*" PATTERN "*.inc"
)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/glog)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/soil)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/soil/inc/SOIL
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*" 
)

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



