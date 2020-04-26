#ifndef SOFTRD_LIGHT_H_
#define SOFTRD_LIGHT_H_

#include "src/components/material.h"
#include "src/math/vector.h"

namespace softrd {

struct Light {
  math::vec3 position;

  math::vec3 ambient;
  math::vec3 diffuse;
  math::vec3 specular;

  Light(const math::vec3 &position = math::vec3(),
        const math::vec3 &ambient = math::vec3(),
        const math::vec3 &diffuse = math::vec3(),
        const math::vec3 &specular = math::vec3())
      : position(position),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular) {}

  virtual math::vec3 CalcColor(const math::vec3 &normal,
                               const math::vec3 &object_position,
                               const math::vec3 &view_dir,
                               const Material &material) {
    // diffuse
    math::vec3 light_dir = (position - object_position).Normalize();
    float diff = math::Max(normal * light_dir, 0.0);

    // specular
    math::vec3 reflect_dir = Reflect(-light_dir, normal);
    float spec =
        pow(math::Max(view_dir * reflect_dir, 0.0), material.shininess);

    math::vec3 ambient_color = ambient.Multiply(material.ambient);
    math::vec3 diffuse_color = diffuse.Multiply(diff * material.diffuse);
    math::vec3 specular_color = specular.Multiply(spec * material.specular);

    return ambient_color + diffuse_color + specular_color;
  }
};

struct DirLight : public Light {  // Directional Light
  math::vec3 direction;

  DirLight(const math::vec3 &direction = math::vec3(),
           const math::vec3 &ambient = math::vec3(),
           const math::vec3 &diffuse = math::vec3(),
           const math::vec3 &specular = math::vec3())
      : Light(math::vec3(), ambient, diffuse, specular), direction(direction) {}

  math::vec3 CalcColor(const math::vec3 &normal,
                       const math::vec3 &object_position,
                       const math::vec3 &view_dir, const Material &material) {
    math::vec3 light_dir = (-direction).Normalize();

    // diffuse shading
    float diff = math::Max(normal * light_dir, 0.0);

    // specular shading
    math::vec3 reflect_dir = Reflect(-light_dir, normal);
    float spec =
        pow(math::Max(view_dir * reflect_dir, 0.0), material.shininess);

    // combine results
    math::vec3 ambient_color = ambient.Multiply(material.ambient);
    math::vec3 diffuse_color = diffuse.Multiply(diff * material.diffuse);
    math::vec3 specular_color = specular.Multiply(spec * material.specular);
    return ambient_color + diffuse_color + specular_color;
  }
};

struct PointLight : public Light {
  float constant;
  float linear;
  float quadratic;

  PointLight(const math::vec3 &position = math::vec3(),
             const math::vec3 &ambient = math::vec3(),
             const math::vec3 &diffuse = math::vec3(),
             const math::vec3 &specular = math::vec3(), float constant = 0.0,
             float linear = 0.0, float quadratic = 0.0)
      : Light(position, ambient, diffuse, specular),
        constant(constant),
        linear(linear),
        quadratic(quadratic) {}

  math::vec3 CalcColor(const math::vec3 &normal,
                       const math::vec3 &object_position,
                       const math::vec3 &view_dir, const Material &material) {
    math::vec3 light_dir = (position - object_position);
    float distance = light_dir.Length();
    light_dir.Normalize();

    // diffuse shading
    float diff = math::Max(normal * light_dir, 0.0);

    // specular shading
    math::vec3 reflect_dir = Reflect(-light_dir, normal);
    float spec =
        pow(math::Max(view_dir * reflect_dir, 0.0), material.shininess);
    // attenuation
    float attenuation = 1.0 / (constant + linear * distance +
                               quadratic * (distance * distance));

    // combine results
    math::vec3 ambient_color = ambient.Multiply(material.ambient) * attenuation;
    math::vec3 diffuse_color =
        diffuse.Multiply(diff * material.diffuse) * attenuation;
    math::vec3 specular_color =
        specular.Multiply(spec * material.specular) * attenuation;
    return ambient_color + diffuse_color + specular_color;
  }
};

struct SpotLight : public PointLight {
  math::vec3 direction;
  float cut_off;
  float outer_cut_off;

  SpotLight(const math::vec3 &position = math::vec3(),
            const math::vec3 &direction = math::vec3(), float cut_off = 0.0,
            float outer_cut_off = 0.0, const math::vec3 &ambient = math::vec3(),
            const math::vec3 &diffuse = math::vec3(),
            const math::vec3 &specular = math::vec3(), float constant = 0.0,
            float linear = 0.0, float quadratic = 0.0)
      : PointLight(position, ambient, diffuse, specular, constant, linear,
                   quadratic),
        direction(direction),
        cut_off(cut_off),
        outer_cut_off(outer_cut_off) {}

  math::vec3 CalcColor(const math::vec3 &normal,
                       const math::vec3 &object_position,
                       const math::vec3 &view_dir, const Material &material) {
    math::vec3 light_dir = (position - object_position);
    float distance = light_dir.Length();
    light_dir.Normalize();

    // diffuse shading
    float diff = math::Max(normal * light_dir, 0.0);

    // specular shading
    math::vec3 reflect_dir = Reflect(-light_dir, normal);
    float spec =
        pow(math::Max(view_dir * reflect_dir, 0.0), material.shininess);
    // attenuation
    float attenuation = 1.0 / (constant + linear * distance +
                               quadratic * (distance * distance));

    // spot light (soft edges)
    float theta =
        light_dir *
        (-direction)
            .Normalize();  // in opengl tutorial it's (-direction).Normalize()
    float epsilon = cut_off - outer_cut_off;
    float intensity = math::Clamp((theta - outer_cut_off) / epsilon, 0.0, 1.0);

    // combine results
    math::vec3 ambient_color = ambient.Multiply(material.ambient) * attenuation;
    math::vec3 diffuse_color =
        diffuse.Multiply(diff * material.diffuse) * attenuation * intensity;
    math::vec3 specular_color =
        specular.Multiply(spec * material.specular) * attenuation * intensity;
    return ambient_color + diffuse_color + specular_color;
  }
};

}  // namespace softrd

#endif  // SOFTRD_LIGHT_H_