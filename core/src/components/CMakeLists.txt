add_library(components model.cc)
target_link_libraries(components ${ASSIMP_LIB} ${SOIL_LIB})