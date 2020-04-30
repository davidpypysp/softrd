include_directories(${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/abseil-cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/soil/inc)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/assimp/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/build/third_party/assimp/include)

find_library(CORE_API SoftrdAPI
    PATHS ${CMAKE_CURRENT_LIST_DIR}/build/src/interface
)

