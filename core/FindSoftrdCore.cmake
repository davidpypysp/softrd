include_directories(${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/abseil-cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/soil/inc)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/assimp/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/build/third_party/assimp/include)

add_library(SoftrdAPI SHARED IMPORTED)
set_property(TARGET SoftrdAPI PROPERTY IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/build/my_archive/Release/SoftrdAPI.lib)