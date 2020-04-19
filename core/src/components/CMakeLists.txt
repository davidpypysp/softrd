add_library(components model.cc)
target_link_libraries(components assimp soil GL absl::str_format_internal)