#ifndef SOFTRD_VERTEX_SHADER_H_
#define SOFTRD_VERTEX_SHADER_H_

#include "src/components/vertex.h"
#include "src/math/matrix.h"
#include "src/math/vector.h"

namespace softrd {

// contain clipping space position
struct VertexOut {
  vec4 position;  // clipping space position
  vec3 world_position;
  vec3 world_normal;
  vec2 uv;
};

class VertexShader {
 public:
  mat4 transform() const { return transform_; }
  void set_transform(const mat4 &transform) { transform_ = transform; }

  VertexShader();
  bool Run(const Vertex &in, VertexOut *out);
  virtual bool Program();

 protected:
  mat4 transform_;

  Vertex in_;
  VertexOut *out_;
};

class VertexShaderLight : public VertexShader {
 public:
  mat4 model() const { return model_; }
  void set_model(const mat4 &model) { model_ = model; }

 protected:
  mat4 model_;

  bool Program();
};

}  // namespace softrd

#endif  // SOFTRD_VERTEX_SHADER_H_