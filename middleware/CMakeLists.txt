project (SoftrdJs)

set(CORE_DIR ${CMAKE_SOURCE_DIR}/../core CACHE STRING "Some user-specified option")

message("CORE_DIR: " ${CORE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CORE_DIR})
find_package(SoftrdCore)

include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES 
        ${CMAKE_SOURCE_DIR}/src/addon_init.cc
        ${CMAKE_SOURCE_DIR}/src/renderer_api_addon.cc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
message("NODE_ADDON_API_DIR" ${NODE_ADDON_API_DIR})
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

message(AUTHOR_WARNING "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})


set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_link_libraries(${PROJECT_NAME} renderer_api)
