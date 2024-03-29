#ifndef SOFTRD_FRAGMENT_SHADER_H_
#define SOFTRD_FRAGMENT_SHADER_H_

#include <iostream>
#include <memory>
#include <vector>

#include "src/common/fragment.h"
#include "src/common/light.h"
#include "src/common/material.h"
#include "src/common/texture.h"

namespace softrd {

struct FragmentOut {
  math::vec3 window_position;
  math::vec4 color;
};

class FragmentShader {
 public:
  Fragment in_;
  FragmentOut *out_;
  Texture *texture_;

  FragmentShader();
  virtual void Program();
  void Run(const Fragment &in, FragmentOut *out);
  void set_texture(Texture *texture) { texture_ = texture; };

 private:
};

class FragmentShaderFlatColor : public FragmentShader {
 public:
  math::vec3 flat_color;

  FragmentShaderFlatColor(const math::vec3 &color = math::vec3());
  void Program();
};

class FragmentShaderLight : public FragmentShader {
 public:
  math::vec3 object_color;
  math::vec3 light_color;
  math::vec3 light_position;
  math::vec3 view_position;

  void Program();
};

class FragmentShaderLightFull : public FragmentShader {
 public:
  math::vec3 *view_position_ = nullptr;
  std::shared_ptr<Material> material_ = nullptr;
  std::vector<Light *> lights;

  FragmentShaderLightFull(math::vec3 *view_position,
                          std::shared_ptr<Material> material);
  void Program();
  void AddLight(Light *light);
};

class FragmentShaderLightTexture : public FragmentShader {
 public:
  math::vec3 &view_position;
  TextureMaterial &material;
  std::vector<Light *> lights;

  FragmentShaderLightTexture(math::vec3 &view_position,
                             TextureMaterial &material);
  void Program();
  void AddLight(Light *light);
};

}  // namespace softrd

#endif  // SOFTRD_FRAGMENT_SHADER_H_