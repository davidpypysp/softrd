message(WARNING "renderer/ path: " ${CMAKE_CURRENT_SOURCE_DIR})


add_library (renderer rendering_pipeline.cc)
link_directories(${CMAKE_SOURCE_DIR}/src/modules)
target_link_libraries(renderer modules)

message(WARNING "librenderer: " ${renderer})
