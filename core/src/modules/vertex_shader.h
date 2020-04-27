#ifndef SOFTRD_VERTEX_SHADER_H_
#define SOFTRD_VERTEX_SHADER_H_

#include "src/common/vertex.h"
#include "src/math/matrix.h"
#include "src/math/vector.h"

namespace softrd {

// contain clipping space position
struct VertexOut {
  math::vec4 position;  // clipping space position
  math::vec3 world_position;
  math::vec3 world_normal;
  math::vec2 uv;
};

class VertexShader {
 public:
  math::mat4 transform() const { return transform_; }
  void set_transform(const math::mat4 &transform) { transform_ = transform; }

  VertexShader();
  bool Run(const Vertex &in, VertexOut *out);
  virtual bool Program();

 protected:
  math::mat4 transform_;

  Vertex in_;
  VertexOut *out_;
};

class VertexShaderLight : public VertexShader {
 public:
  math::mat4 model() const { return model_; }
  void set_model(const math::mat4 &model) { model_ = model; }

 protected:
  math::mat4 model_;

  bool Program();
};

}  // namespace softrd

#endif  // SOFTRD_VERTEX_SHADER_H_