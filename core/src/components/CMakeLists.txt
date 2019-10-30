message(WARNING "components/ path: " ${CMAKE_CURRENT_SOURCE_DIR})

message(WARNING "cmake_prefix_path: " "${CMAKE_PREFIX_PATH}")

find_library(ASSIMP_LIB assimp)
message(WARNING "assimp_lib: " ${ASSIMP_LIB})

find_library(SOIL_LIB soil)
message(WARNING "soil_lib: " ${SOIL_LIB})


find_library(GL_LIB GL)
message(WARNING "gl_lib: " ${GL_LIB})


add_library (components model.cc)
target_link_libraries(components "${ASSIMP_LIB}" "${SOIL_LIB}" "${GL_LIB}")