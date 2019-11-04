
aux_source_directory(. DIR_SRCS)

add_library (modules ${DIR_SRCS})
target_link_libraries(modules components)

