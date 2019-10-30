
aux_source_directory(. DIR_LIB_SRCS)
message(WARNING "dir_srcs: " ${DIR_LIB_SRCS})

add_library (modules ${DIR_LIB_SRCS})
