#ifndef SOFTRD_VERTEX_H_
#define SOFTRD_VERTEX_H_

#include "src/math/vector.h"

namespace softrd {

// vertex contains position, normal, texutre_mapping...
struct Vertex {
  math::vec3 position;
  math::vec3 normal;
  math::vec2 uv;

  Vertex(const math::vec3 &position = math::vec3(),
         const math::vec3 &normal = math::vec3(),
         const math::vec2 &uv = math::vec2())
      : position(position), normal(normal), uv(uv) {}
};

}  // namespace softrd

#endif  // SOFTRD_VERTEX_H_
