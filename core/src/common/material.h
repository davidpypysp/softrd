#ifndef SOFTRD_MATERIAL_H_
#define SOFTRD_MATERIAL_H_

#include "src/common/texture.h"
#include "src/math/vector.h"

namespace softrd {

struct Material {
  math::vec3 ambient;
  math::vec3 diffuse;
  math::vec3 specular;
  float shininess;

  Material(const math::vec3 &ambient = math::vec3(),
           const math::vec3 &diffuse = math::vec3(),
           const math::vec3 &specular = math::vec3(),
           const float shininess = 0.0)
      : ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess) {}
};

struct TextureMaterial {
  Texture *diffuse_texture;
  Texture *specular_texture;

  float shininess;

  TextureMaterial(Texture *diffuse = nullptr, Texture *specular = nullptr,
                  const float shininess = 0.0)
      : diffuse_texture(diffuse),
        specular_texture(specular),
        shininess(shininess) {}
};

}  // namespace softrd

#endif  // SOFTRD_MATERIAL_H_