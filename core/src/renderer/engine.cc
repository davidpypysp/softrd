#include "src/renderer/engine.h"

namespace softrd {

Engine::Engine() {
  scene_manager_ = std::make_shared<SceneManager>();
  rendering_pipeline_ = std::make_unique<RenderingPipeline>();
}

void Engine::Reset(const int width, const int height) {
  if (!scene_manager_ || !rendering_pipeline_) {
    return;
  }
  rendering_pipeline_->Reset(width, height, scene_manager_->default_camera());
}

void Engine::DrawSceneObjects() {
  rendering_pipeline_->ResetBuffer();

  const auto& scene_objects = scene_manager_->scene_objects();

  for (const auto& it : scene_objects) {
    auto scene_object = it.second;

    rendering_pipeline_->DrawSceneObject(scene_object);
  }
}

void Engine::DrawScene() {
  rendering_pipeline_->ResetBuffer();
  this->DrawSceneObjects();
}

}  // namespace softrd