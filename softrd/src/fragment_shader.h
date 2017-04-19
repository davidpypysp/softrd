#ifndef SOFTRD_FRAGMENT_SHADER_H_
#define SOFTRD_FRAGMENT_SHADER_H_

#include "fragment.h"

namespace softrd {

struct FragmentOut {
	vec3 window_position;
	vec4 color;
};


class FragmentShader {
public:
	FragmentShader();
	void Run(const Fragment &in, FragmentOut *out);
};

} // namespace softrd

#endif // SOFTRD_FRAGMENT_SHADER_H_