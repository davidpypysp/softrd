#ifndef SOFTRD_RENDER_ENGINE_H_
#define SOFTRD_RENDER_ENGINE_H_

#include "src/renderer/rendering_pipeline.h"
#include "src/renderer/scene_manager.h"

namespace softrd {

class RenderEngine {
 public:
  RenderEngine();

 private:
  std::unique_ptr<RenderingPipeline> rendering_pipeline_ = nullptr;
  std::unique_ptr<SceneManager> scene_manager_ = nullptr;
};

}  // namespace softrd

#endif  // SOFTRD_RENDER_ENGINE_H_