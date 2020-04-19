add_library(components model.cc)
target_link_libraries(components ${ASSIMP_LIB} soil GL absl::str_format_internal)