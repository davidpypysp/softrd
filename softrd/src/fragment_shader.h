#ifndef SOFTRD_FRAGMENT_SHADER_H_
#define SOFTRD_FRAGMENT_SHADER_H_

#include <iostream>

#include "fragment.h"
#include "texture.h"
#include "light.h"
#include "material.h"

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

	vec3 &view_position;
	Material &material;
	Light &light;

	FragmentShaderLightFull(vec3 &view_position = vec3(), Material &material = Material(), Light &light = Light());
	void Program();

};

class FragmentShaderLightTexture : public FragmentShader {
public:

	vec3 &view_position;
	TextureMaterial &material;
	Light &light;

	FragmentShaderLightTexture(vec3 &view_position = vec3(), TextureMaterial &material = TextureMaterial(), Light &light = Light());
	void Program();

};





} // namespace softrd

#endif // SOFTRD_FRAGMENT_SHADER_H_