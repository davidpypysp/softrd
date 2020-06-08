# gtest
set(GTest_DIR ${CMAKE_CURRENT_LIST_DIR}/wasm/googletest/lib/cmake/GTest)
find_package(GTest CONFIG REQUIRED)

# assimp
set(assimp_DIR ${CMAKE_CURRENT_LIST_DIR}/wasm/assimp)
add_library(assimp::assimp STATIC IMPORTED)
set_target_properties(assimp::assimp PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${assimp_DIR}/include"
  IMPORTED_LOCATION_RELEASE "${assimp_DIR}/lib/libassimp.a"
  IMPORTED_CONFIGURATIONS RELEASE
)
target_link_libraries(assimp::assimp INTERFACE 
    ${assimp_DIR}/lib/libIrrXML.a
    ${assimp_DIR}/lib/libzlibstatic.a
)

# SOIL
set(SOIL_DIR ${CMAKE_CURRENT_LIST_DIR}/wasm/soil)
add_library(soil::soil STATIC IMPORTED)
set_target_properties(soil::soil PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${SOIL_DIR}/include"
  IMPORTED_LOCATION_RELEASE "${SOIL_DIR}/lib/libSOIL.bc"
  IMPORTED_CONFIGURATIONS RELEASE
)