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
	FragmentShader();
	virtual void Run(const Fragment &in, FragmentOut *out);

	void set_texture(Texture *texture) { texture_ = texture; };

private:
	Texture *texture_;

};


class FragmentShader1 : public FragmentShader {
	void Run(const Fragment &in, FragmentOut *out);

};



} // namespace softrd

#endif // SOFTRD_FRAGMENT_SHADER_H_