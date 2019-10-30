message(WARNING "components/ path: " ${CMAKE_CURRENT_SOURCE_DIR})

message(WARNING "cmake_prefix_path: " "${CMAKE_PREFIX_PATH}")

find_library(ASSIMP_LIB assimp)
message(WARNING "assimp_lib: " ${ASSIMP_LIB})

add_library (components model.cc)
target_link_libraries(components "${ASSIMP_LIB}")