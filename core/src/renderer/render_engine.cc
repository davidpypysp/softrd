#include "src/renderer/render_engine.h"

namespace softrd {

RenderEngine::RenderEngine() {
  // this->rendering_pipeline_=std::unique_ptr<RenderingPipeline>(new
  // RenderingPipeline());
  this->scene_manager_ = std::unique_ptr<SceneManager>(new SceneManager());
}

}  // namespace softrd