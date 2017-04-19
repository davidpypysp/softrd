#include "fragment_shader.h"

namespace softrd {

FragmentShader::FragmentShader() {
}

void FragmentShader::Run(const Fragment &in, FragmentOut *out) {
	out->window_position = in.window_position;
	out->color = vec4(1.0, 1.0, 0.0, 1.0);
}

} // namespace softrd