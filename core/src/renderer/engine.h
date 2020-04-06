#ifndef SOFTRD_ENGINE_H_
#define SOFTRD_ENGINE_H_

#include "src/renderer/rendering_pipeline.h"
#include "src/renderer/scene_manager.h"

namespace softrd {

class Engine {
 public:
  Engine();
  void Reset(const int width, const int height);
  void DrawSceneObjects();
  void DrawScene(uint8_t *buffer);

  std::shared_ptr<SceneManager> scene_manager() const { return scene_manager_; }

 private:
  std::unique_ptr<RenderingPipeline> rendering_pipeline_ = nullptr;
  std::shared_ptr<SceneManager> scene_manager_ = nullptr;
};

}  // namespace softrd

#endif  // SOFTRD_ENGINE_H_