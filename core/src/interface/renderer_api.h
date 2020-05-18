#ifndef SOFTRD_RENDERER_API_H_
#define SOFTRD_RENDERER_API_H_

#include <vector>

#include "src/renderer/engine.h"

namespace softrd {

class RendererAPI : public Engine {
 public:
  RendererAPI();

  void ResetBuffer(uint8_t *buffer, size_t size);
  void SetSceneObject(const std::string &id, const math::vec3 &position,
                      const math::vec3 &rotation);
};

}  // namespace softrd

#endif  // SOFTRD_RENDERER_API_H_