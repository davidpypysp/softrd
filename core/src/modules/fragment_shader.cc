#include "src/modules/fragment_shader.h"

#include "src/math/math_util.h"

namespace softrd {

FragmentShader::FragmentShader() {}

void FragmentShader::Program() { out_->color = math::vec4(1.0, 1.0, 1.0, 1.0); }

void FragmentShader::Run(const Fragment &in, FragmentOut *out) {
  in_ = in;
  out_ = out;
  out->window_position = in.window_position;
  Program();
}

FragmentShaderFlatColor::FragmentShaderFlatColor(const math::vec3 &color)
    : flat_color(color) {}

void FragmentShaderFlatColor::Program() {
  out_->color = math::vec4(flat_color, 1.0);
}

void FragmentShaderLight::Program() {
  // ambient
  float ambientStrength = 0.1;
  math::vec3 ambient = ambientStrength * light_color;

  // diffuse
  math::vec3 norm = in_.world_normal.Normalize();
  math::vec3 light_dir = (light_position - in_.world_position).Normalize();

  float diff = math::Max(norm * light_dir, 0.0);
  math::vec3 diffuse = diff * light_color;

  // specular
  float specular_strength = 0.5;
  math::vec3 view_dir = (view_position - in_.world_position).Normalize();
  math::vec3 reflect_dir = Reflect(-light_dir, norm);
  // math::vec3 reflect_dir = (2.0 * (light_dir * norm) * norm) - light_dir;
  float spec = pow(math::Max(view_dir * reflect_dir, 0.0), 32);
  math::vec3 specular = specular_strength * spec * light_color;

  math::vec3 result = (ambient + diffuse + specular).Multiply(object_color);
  out_->color = math::vec4(result, 1.0);
}

FragmentShaderLightFull::FragmentShaderLightFull(
    math::vec3 *view_position, std::shared_ptr<Material> material)
    : view_position_(view_position), material_(material) {}

void FragmentShaderLightFull::Program() {
  math::vec3 norm = in_.world_normal.Normalize();
  math::vec3 view_dir = (*view_position_ - in_.world_position).Normalize();

  math::vec3 result;
  for (Light *light : lights) {
    result = result +
             light->CalcColor(norm, in_.world_position, view_dir, *material_);
  }
  out_->color = math::vec4(result, 1.0);
}

void FragmentShaderLightFull::AddLight(Light *light) {
  lights.push_back(light);
}

FragmentShaderLightTexture::FragmentShaderLightTexture(
    math::vec3 &view_position, TextureMaterial &material)
    : view_position(view_position), material(material) {}

void FragmentShaderLightTexture::Program() {
  math::vec3 diffuse_tex = material.diffuse_texture->GetColor(in_.uv);
  math::vec3 specular_tex = material.specular_texture->GetColor(in_.uv);
  Material fragment_material(diffuse_tex, diffuse_tex, specular_tex,
                             material.shininess);

  math::vec3 normal = in_.world_normal;
  normal.Normalize();
  math::vec3 view_dir = (view_position - in_.world_position).Normalize();

  math::vec3 result;

  for (int i = 0; i < lights.size(); i++) {
    result = result + lights[i]->CalcColor(normal, in_.world_position, view_dir,
                                           fragment_material);
  }
  out_->color = math::vec4(result, 1.0);
}

void FragmentShaderLightTexture::AddLight(Light *light) {
  lights.push_back(light);
}

}  // namespace softrd