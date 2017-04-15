#include "vertex_shader.h"

namespace softrd {

VertexShader::VertexShader() {}


// input vertex and output after certain transformation
VertexOut VertexShader::Run(const Vertex &in) {
	VertexOut out;
	vec4 world_position = model_ * vec4(in.position, 1.0);
	vec4 eye_position = view_ * world_position;
	out.world_position = vec3(world_position.x, world_position.y, world_position.z);
	out.position = transform_ * vec4(in.position, 1.0);

	mat4 rotation = model_;
	rotation[0][3] = rotation[1][3] = rotation[2][3] = 0.0; // skip traslation matrix
	double scale_factor = sqrt(rotation[0][0] * rotation[0][0] + rotation[1][0] * rotation[1][0] + rotation[2][0] * rotation[2][0]);
	assert(scale_factor != 0.0);
	for (int i = 0; i < 3; ++i) { // skip uniform scaling matrix
		for (int j = 0; j < 3; ++j)
			rotation[i][j] /= scale_factor;
	}
	out.uv = in.uv;
	return out;
}




} // namespace softrd
