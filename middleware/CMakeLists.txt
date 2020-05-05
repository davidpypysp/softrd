project (SoftrdJs)
cmake_minimum_required (VERSION 2.6)

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++17")
endif()

# install for frontend by default
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../frontend)

set(CORE_DIR ${CMAKE_SOURCE_DIR}/build-core CACHE STRING "Softrd core dir path")

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

include_directories(${CMAKE_JS_INC})
include_directories(${CORE_DIR}/include)

file(GLOB SRC_CC ${CMAKE_SOURCE_DIR}/src/*.cc)

add_library(${PROJECT_NAME} SHARED ${SRC_CC} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

set(CORE_SHARED_LIB ${CORE_DIR}/lib/SoftrdAPI.dll)


add_library(SoftrdAPI SHARED IMPORTED)
if(MSVC)
  set_property(TARGET SoftrdAPI PROPERTY IMPORTED_IMPLIB ${CORE_DIR}/lib/SoftrdAPI.lib)
  set_property(TARGET SoftrdAPI PROPERTY IMPORTED_LOCATION ${CORE_SHARED_LIB})
endif()

target_link_libraries(${PROJECT_NAME} SoftrdAPI)

if(MSVC)
  file(COPY ${CORE_SHARED_LIB} DESTINATION ${CMAKE_BINARY_DIR}/Release/)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

add_definitions(-DNAPI_VERSION=3)


install(DIRECTORY ${CMAKE_BINARY_DIR}/Release/ DESTINATION Release)