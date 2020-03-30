#include "src/renderer/engine.h"

namespace softrd {

Engine::Engine() {
  scene_manager_ = std::make_unique<SceneManager>();
  rendering_pipeline_ = std::make_unique<RenderingPipeline>();
}

void Engine::Reset(const int width, const int height) {
  if (!scene_manager_ || !rendering_pipeline_) return;

  rendering_pipeline_->Reset(640, 480, scene_manager_->camera());
}

void Engine::DrawSceneObjects() {
  const auto& scene_objects = scene_manager_->scene_objects();

  for (const auto& it : scene_objects) {
    auto scene_object = it.second;
  }
}

}  // namespace softrd