#include "fragment_shader.h"

#define RUN_PROGRAM(func)  func##(in, out);

namespace softrd {

FragmentShader::FragmentShader() {
}

void FragmentShader::Run(const Fragment &in, FragmentOut *out) {
	out->window_position = in.window_position;
	out->color = vec4(1.0, 1.0, 1.0, 1.0);
}



void FragmentShader1::Run(const Fragment & in, FragmentOut * out) {
	out->window_position = in.window_position;

	//vec3 color = texture_->GetColor(in.uv.x, in.uv.y);
	//out->color = vec4(color.x, color.y, color.z, 1.0);
	out->color = vec4(0.4, 0.8, 0.67, 1.0);
}

} // namespace softrd