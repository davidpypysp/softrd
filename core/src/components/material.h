#ifndef SOFTRD_MATERIAL_H_
#define SOFTRD_MATERIAL_H_

#include "src/components/texture.h"
#include "src/math/vector.h"

namespace softrd {

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;

  Material(const vec3 &ambient = vec3(), const vec3 &diffuse = vec3(),
           const vec3 &specular = vec3(), const float shininess = 0.0)
      : ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess) {}
};

struct TextureMaterial {
  Texture *specular_texture;
  Texture *diffuse_texture;

  float shininess;

  TextureMaterial(Texture *diffuse = nullptr, Texture *specular = nullptr,
                  const float shininess = 0.0)
      : diffuse_texture(diffuse),
        specular_texture(specular),
        shininess(shininess) {}
};

}  // namespace softrd

#endif  // SOFTRD_MATERIAL_H_