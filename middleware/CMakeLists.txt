cmake_minimum_required (VERSION 3.16)

project (SoftrdJs)

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++17")
endif()

# install for frontend by default
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../frontend)

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

include_directories(${CMAKE_JS_INC})

file(GLOB SRC_CC ${CMAKE_SOURCE_DIR}/src/*.cc)

add_library(${PROJECT_NAME} SHARED ${SRC_CC} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# import core target
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_SOURCE_DIR}/build-core)
find_package(SoftrdCore CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} SoftrdAPI)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
add_definitions(-DNAPI_VERSION=3)

install(DIRECTORY ${CMAKE_BINARY_DIR}/Release/ DESTINATION Release)