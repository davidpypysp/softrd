#include "fragment_shader.h"

namespace softrd {

FragmentShader::FragmentShader() {
}

void FragmentShader::Run() {
	out_.window_position = in_.window_position;
	out_.color = vec4(1.0, 1.0, 0.0, 1.0);
}

} // namespace softrd