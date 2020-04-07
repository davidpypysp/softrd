#ifndef SOFTRD_RENDERER_API_H_
#define SOFTRD_RENDERER_API_H_

#include <vector>

#include "src/renderer/engine.h"
#include "src/renderer/rendering_pipeline.h"

namespace softrd {

class RendererAPI {
 public:
  RendererAPI();

  void ResetBuffer(uint8_t *buffer, size_t size);
  void DrawScene(uint8_t *buffer);
  void SetSceneObject(const std::string &id, const vec3 &position,
                      const vec3 &rotation);

  ~RendererAPI();

 private:
  std::unique_ptr<Engine> engine_ = nullptr;
};

}  // namespace softrd

#endif  // SOFTRD_RENDERER_API_H_