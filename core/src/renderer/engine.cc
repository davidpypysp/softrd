#include "src/renderer/engine.h"

namespace softrd {

Engine::Engine() {
  // this->rendering_pipeline_=std::unique_ptr<RenderingPipeline>(new
  // RenderingPipeline());
  this->scene_manager_ = std::unique_ptr<SceneManager>(new SceneManager());
}

}  // namespace softrd