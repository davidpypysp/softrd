include_directories(${CMAKE_CURRENT_LIST_DIR}/wasm/soil/include)
# include_directories(${CMAKE_CURRENT_LIST_DIR}/wasm/assimp/include)

set(SOIL_LIB ${CMAKE_SOURCE_DIR}/third_party/wasm/soil/lib/libSOIL.bc)

set(GTest_DIR ${CMAKE_CURRENT_LIST_DIR}/wasm/googletest/lib/cmake/GTest)
find_package(GTest CONFIG REQUIRED)

# assimp
set(assimp_DIR ${CMAKE_CURRENT_LIST_DIR}/wasm/assimp)

add_library(assimp::assimp STATIC IMPORTED)
set_target_properties(assimp::assimp PROPERTIES
  COMPATIBLE_INTERFACE_STRING "assimp_MAJOR_VERSION"
  INTERFACE_assimp_MAJOR_VERSION "1"
  INTERFACE_INCLUDE_DIRECTORIES "${assimp_DIR}/include"
)
set_property(TARGET assimp::assimp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(assimp::assimp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${assimp_DIR}/lib/libassimp.a"
)

target_link_libraries(assimp::assimp INTERFACE 
    ${assimp_DIR}/lib/libIrrXML.a
    ${assimp_DIR}/lib/libzlibstatic.a
)