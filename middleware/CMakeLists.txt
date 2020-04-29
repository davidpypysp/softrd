project (hello)

include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/hello.cc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})


execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
message("NODE_ADDON_API_DIR" ${NODE_ADDON_API_DIR})
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

message("CMAKE_JS_INC" ${CMAKE_JS_INC})
message("CMAKE_JS_LIB" ${CMAKE_JS_LIB})


set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})