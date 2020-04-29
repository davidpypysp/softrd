message("I'm softrd core!!! " ${CORE_DIR})
message("CMAKE_CURRENT_LIST_DIR: " ${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/abseil-cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/soil/inc)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/assimp/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/build/third_party/assimp/include)

# Your-external "mylib", add GLOBAL if the imported library is located in directories above the current.
add_library(renderer_api SHARED IMPORTED )
# You can define two import-locations: one for debug and one for release.
set_target_properties(renderer_api PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/build/src/interface/libSoftrdAPI.so)
