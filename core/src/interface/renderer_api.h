#ifndef SOFTRD_RENDERER_API_H_
#define SOFTRD_RENDERER_API_H_

#include "src/renderer/rendering_pipeline.h"

#include <vector>

namespace softrd {

class RendererAPI {
 public:
  RendererAPI();

  void InitExampleMesh();
  void DrawExampleMesh();

  ~RendererAPI();

 private:
  RenderingPipeline rendering_pipeline_;

  Mesh example_cube_;
};

}  // namespace softrd

#endif  // SOFTRD_RENDERER_API_H_