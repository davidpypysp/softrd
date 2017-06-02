#include "vertex_shader.h"

namespace softrd {

VertexShader::VertexShader() {}


// input vertex and output after certain transformation
bool VertexShader::Run(const Vertex &in, VertexOut *out) {
	out->position = transform_ * vec4(in.position, 1.0);
	return true;
}




bool VertexShaderLight::Run(const Vertex &in, VertexOut *out) {
	vec4 world_position = model_ * vec4(in.position, 1.0);
	out->world_position = vec3(world_position.x, world_position.y, world_position.z);
	out->position = transform_ * vec4(in.position, 1.0);

	mat4 rotation = model_;
	rotation.translate(0.0, 0.0, 0.0); // skip traslation matrix
	double scale_factor = sqrt(rotation[0][0] * rotation[0][0] + rotation[1][0] * rotation[1][0] + rotation[2][0] * rotation[2][0]);
	assert(scale_factor != 0.0);
	for (int i = 0; i < 3; ++i) { // skip uniform scaling matrix
		for (int j = 0; j < 3; ++j)
			rotation[i][j] /= scale_factor;
	}
	vec4 world_normal = rotation * vec4(in.normal, 1.0);
	out->world_normal = vec3(world_normal.x, world_normal.y, world_normal.z);

	out->uv = in.uv;
	return true;
}

} // namespace softrd
