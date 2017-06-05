#ifndef SOFTRD_LIGHT_H_
#define SOFTRD_LIGHT_H_

#include "math/vector.h"
#include "material.h"

namespace softrd {

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	Light(const vec3 &position = vec3(), const vec3 &ambient = vec3(), const vec3 &diffuse = vec3(), const vec3 &specular = vec3()) :
		position(position),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular) {
	}


};


struct DirLight { // Directional Light
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	DirLight(const vec3 &direction = vec3(), const vec3 &ambient = vec3(), const vec3 &diffuse = vec3(), const vec3 &specular = vec3()) :
		direction(direction),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular) {
	}

	vec3 CalcColor(const vec3 &normal, const vec3 &view_dir, const Material &material) {
		vec3 light_dir = (-direction).normalize();


		// diffuse shading
		float diff = Max(normal * light_dir, 0.0);

		// specular shading
		vec3 reflect_dir = Reflect(-light_dir, normal);
		float spec = pow(Max(view_dir * reflect_dir, 0.0), material.shininess);

		// combine results
		vec3 ambient = ambient.multiply(material.ambient);
		vec3 diffuse = diffuse.multiply(diff * material.diffuse);
		vec3 specular = specular.multiply(spec * material.specular);
		return (ambient + diffuse + specular);
	}
};


struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	PointLight(const vec3 &position = vec3(), const vec3 &ambinet = vec3(), const vec3 &diffuse = vec3(), const vec3 &specular = vec3(), float constant = 0.0, float linear = 0.0, float quadratic = 0.0) :
		position(position),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		constant(constant),
		linear(linear),
		quadratic(quadratic) {
	}


	vec3 CalcColor(const vec3 &normal, const vec3 &object_position, const vec3 &view_dir, const Material &material) {

		vec3 light_dir = (position - object_position);
		float distance = light_dir.length();
		light_dir.normalize();

		// diffuse shading
		float diff = Max(normal * light_dir, 0.0);

		// specular shading
		vec3 reflect_dir = Reflect(-light_dir, normal);
		float spec = pow(Max(view_dir * reflect_dir, 0.0), material.shininess);
		// attenuation
		float attenuation = 1.0 / (constant + linear * distance +
			quadratic * (distance * distance));

		// combine results
		vec3 ambient = ambient.multiply(material.ambient) * attenuation;
		vec3 diffuse = diffuse.multiply(diff * material.diffuse) * attenuation;
		vec3 specular = specular.multiply(spec * material.specular) * attenuation;
		return (ambient + diffuse + specular);
	}
};


} // namespace softrd




#endif // SOFTRD_LIGHT_H_