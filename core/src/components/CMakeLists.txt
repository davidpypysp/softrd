message(WARNING "components/ path: " ${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(. DIR_SRCS)
message(WARNING "dir_srcs: " ${DIR_SRCS})

add_library (components model.cc)
