#ifndef SOFTRD_LIGHT_H_
#define SOFTRD_LIGHT_H_

#include "src/math/vector.h"
#include "src/components/material.h"

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

	virtual vec3 CalcColor(const vec3 &normal, const vec3 &object_position, const vec3 &view_dir, const Material &material) {

		// diffuse 
		vec3 light_dir = (position - object_position).normalize();
		float diff = Max(normal * light_dir, 0.0);

		// specular
		vec3 reflect_dir = Reflect(-light_dir, normal);
		float spec = pow(Max(view_dir * reflect_dir, 0.0), material.shininess);


		vec3 ambient_color = ambient.multiply(material.ambient);
		vec3 diffuse_color = diffuse.multiply(diff * material.diffuse);
		vec3 specular_color = specular.multiply(spec * material.specular);

		return ambient_color + diffuse_color + specular_color;
	}

};


struct DirLight : public Light { // Directional Light
	vec3 direction;

	DirLight(const vec3 &direction = vec3(), const vec3 &ambient = vec3(), const vec3 &diffuse = vec3(), const vec3 &specular = vec3()) :
		Light(vec3(), ambient, diffuse, specular),
		direction(direction) {
	}

	vec3 CalcColor(const vec3 &normal, const vec3 &object_position, const vec3 &view_dir, const Material &material) {
		vec3 light_dir = (-direction).normalize();


		// diffuse shading
		float diff = Max(normal * light_dir, 0.0);

		// specular shading
		vec3 reflect_dir = Reflect(-light_dir, normal);
		float spec = pow(Max(view_dir * reflect_dir, 0.0), material.shininess);

		// combine results
		vec3 ambient_color = ambient.multiply(material.ambient);
		vec3 diffuse_color = diffuse.multiply(diff * material.diffuse);
		vec3 specular_color = specular.multiply(spec * material.specular);
		return ambient_color + diffuse_color + specular_color;
	}
};


struct PointLight : public Light {
	float constant;
	float linear;
	float quadratic;

	PointLight(const vec3 &position = vec3(), const vec3 &ambient = vec3(), const vec3 &diffuse = vec3(), const vec3 &specular = vec3(), float constant = 0.0, float linear = 0.0, float quadratic = 0.0) :
		Light(position, ambient, diffuse, specular),
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
		float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

		// combine results
		vec3 ambient_color = ambient.multiply(material.ambient) * attenuation;
		vec3 diffuse_color = diffuse.multiply(diff * material.diffuse) * attenuation;
		vec3 specular_color = specular.multiply(spec * material.specular) * attenuation;
		return ambient_color + diffuse_color + specular_color;
	}
};

struct SpotLight : public PointLight {
	vec3 direction;
	float cut_off;
	float outer_cut_off;

	SpotLight(const vec3 &position = vec3(), const vec3 &direction = vec3(), float cut_off = 0.0, float outer_cut_off = 0.0, const vec3 &ambient = vec3(), const vec3 &diffuse = vec3(), const vec3 &specular = vec3(), float constant = 0.0, float linear = 0.0, float quadratic = 0.0) :
		PointLight(position, ambient, diffuse, specular, constant, linear, quadratic),
		direction(direction),
		cut_off(cut_off),
		outer_cut_off(outer_cut_off) {
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
		float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

		// spot light (soft edges)
		float theta = light_dir * (-direction).normalize(); // in opengl tutorial it's (-direction).normalize()
		float epsilon = cut_off - outer_cut_off;
		float intensity = Clamp((theta - outer_cut_off) / epsilon, 0.0, 1.0);


		// combine results
		vec3 ambient_color = ambient.multiply(material.ambient) * attenuation;
		vec3 diffuse_color = diffuse.multiply(diff * material.diffuse) * attenuation * intensity;
		vec3 specular_color = specular.multiply(spec * material.specular) * attenuation * intensity;
		return ambient_color + diffuse_color + specular_color;

	}


};


} // namespace softrd




#endif // SOFTRD_LIGHT_H_