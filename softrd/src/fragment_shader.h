#ifndef SOFTRD_FRAGMENT_SHADER_H_
#define SOFTRD_FRAGMENT_SHADER_H_

#include <iostream>

#include "fragment.h"
#include "texture.h"

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


class FragmentShaderLight : public FragmentShader {
public:
	vec3 object_color;
	vec3 light_color;
	vec3 light_position;

	void Program();
};

class FragmentShaderFlatColor : public FragmentShader {
public:
	vec3 flat_color;

	FragmentShaderFlatColor(const vec3 &color = vec3());
	void Program();
};



} // namespace softrd

#endif // SOFTRD_FRAGMENT_SHADER_H_