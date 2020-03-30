#ifndef SOFTRD_RENDERER_API_H_
#define SOFTRD_RENDERER_API_H_

#include "src/renderer/engine.h"
#include "src/renderer/rendering_pipeline.h"

#include <vector>

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
  RenderingPipeline *rendering_pipeline_;
  std::unique_ptr<Engine> engine_ = nullptr;

  Mesh *example_cube_;
};

}  // namespace softrd

#endif  // SOFTRD_RENDERER_API_H_