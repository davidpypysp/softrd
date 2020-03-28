add_library (renderer render_engine.cc scene_manager.cc rendering_pipeline.cc)
target_link_libraries(renderer modules)
