add_library (renderer engine.cc scene_manager.cc rendering_pipeline.cc)
target_link_libraries(renderer modules)
