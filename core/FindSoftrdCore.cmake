include_directories(${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/abseil-cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/soil/inc)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/assimp/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/build/third_party/assimp/include)

add_library(core_renderer_api SHARED IMPORTED )
set_target_properties(core_renderer_api PROPERTIES 
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/build/src/interface/libSoftrdAPI.so
)
