#ifndef SOFTRD_RENDERER_API_H_
#define SOFTRD_RENDERER_API_H_

#include <vector>

#include "src/renderer/engine.h"
#include "src/renderer/rendering_pipeline.h"

namespace softrd {

class RendererAPI {
 public:
  RendererAPI();

  void InitExampleMesh();
  void DrawExampleMesh(uint8_t *buffer);
  void ExamplePrint();
  void ResetBuffer(uint8_t *buffer, size_t size);
  void DrawScene(uint8_t *buffer);

  ~RendererAPI();

 private:
  std::unique_ptr<RenderingPipeline> rendering_pipeline_ = nullptr;
  std::unique_ptr<Engine> engine_ = nullptr;

  std::shared_ptr<Mesh> example_cube_ = nullptr;
};

}  // namespace softrd

#endif  // SOFTRD_RENDERER_API_H_