#include "fragment_shader.h"

namespace softrd {

FragmentShader::FragmentShader() {
}

void FragmentShader::Run(const Fragment &in, FragmentOut *out) {
	out->window_position = in.window_position;

	vec3 color = texture_->GetColor(in.uv.x, in.uv.y);
	out->color = vec4(color.x, color.y, color.z, 1.0);
	//out->color = vec4(1.0, 1.0, 0.0, 1.0);
}

} // namespace softrd