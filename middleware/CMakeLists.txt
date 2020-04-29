project (SoftrdJs)
cmake_minimum_required (VERSION 2.6)

set(CORE_DIR ${CMAKE_SOURCE_DIR}/../core CACHE STRING "Softrd core dir path")

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CORE_DIR})
find_package(SoftrdCore)

include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} renderer_api)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")


