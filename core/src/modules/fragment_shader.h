#ifndef SOFTRD_FRAGMENT_SHADER_H_
#define SOFTRD_FRAGMENT_SHADER_H_

#include <iostream>
#include <memory>
#include <vector>

#include "src/components/fragment.h"
#include "src/components/light.h"
#include "src/components/material.h"
#include "src/components/texture.h"

namespace softrd {

struct FragmentOut {
  vec3 window_position;
  vec4 color;
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
  vec3 flat_color;

  FragmentShaderFlatColor(const vec3 &color = vec3());
  void Program();
};

class FragmentShaderLight : public FragmentShader {
 public:
  vec3 object_color;
  vec3 light_color;
  vec3 light_position;
  vec3 view_position;

  void Program();
};

class FragmentShaderLightFull : public FragmentShader {
 public:
  vec3 *view_position_ = nullptr;
  std::shared_ptr<Material> material_ = nullptr;
  std::vector<Light *> lights;

  FragmentShaderLightFull(vec3 *view_position,
                          std::shared_ptr<Material> material);
  void Program();
  void AddLight(Light *light);
};

class FragmentShaderLightTexture : public FragmentShader {
 public:
  vec3 &view_position;
  TextureMaterial &material;
  std::vector<Light *> lights;

  FragmentShaderLightTexture(vec3 &view_position, TextureMaterial &material);
  void Program();
  void AddLight(Light *light);
};

}  // namespace softrd

#endif  // SOFTRD_FRAGMENT_SHADER_H_