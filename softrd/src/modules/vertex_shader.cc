#include "vertex_shader.h"

namespace softrd {

VertexShader::VertexShader() {}


// input vertex and output after certain transformation
bool VertexShader::Run(const Vertex &in, VertexOut *out) {
	in_ = in;
	out_ = out;
	return Program();
}

bool VertexShader::Program() {
	out_->position = transform_ * vec4(in_.position, 1.0);
	return true;
}


bool VertexShaderLight::Program() {
	out_->position = transform_ * vec4(in_.position, 1.0);

	// world_position
	vec4 world_position = model_ * vec4(in_.position, 1.0);
	out_->world_position = vec3(world_position.x, world_position.y, world_position.z);

	// world_normal
	mat4 rotation = model_;
	rotation.translate(0.0, 0.0, 0.0); // skip traslation matrix
	double scale_factor = sqrt(rotation[0][0] * rotation[0][0] + rotation[1][0] * rotation[1][0] + rotation[2][0] * rotation[2][0]);
	assert(scale_factor != 0.0);
	for (int i = 0; i < 3; ++i) { // skip uniform scaling matrix
		for (int j = 0; j < 3; ++j)
			rotation[i][j] /= scale_factor;
	}
	vec4 world_normal = rotation * vec4(in_.normal, 1.0);
	out_->world_normal = vec3(world_normal.x, world_normal.y, world_normal.z);

	// uv
	out_->uv = in_.uv;
	return true;
}

} // namespace softrd
