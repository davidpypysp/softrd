project (SoftrdJs)
cmake_minimum_required (VERSION 2.6)

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++17")
endif()

set(CORE_DIR ${CMAKE_SOURCE_DIR}/../core CACHE STRING "Softrd core dir path")
message("CORE_DIR" ${CORE_DIR})

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CORE_DIR})
find_package(SoftrdCore)

include_directories(${CMAKE_JS_INC})

file(GLOB SRC_CC ${CMAKE_SOURCE_DIR}/src/*.cc)

add_library(${PROJECT_NAME} SHARED ${SRC_CC} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

target_link_libraries(${PROJECT_NAME} SoftrdAPI)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

add_definitions(-DNAPI_VERSION=3)

