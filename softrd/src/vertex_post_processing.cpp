#include "vertex_post_processing.h"

namespace softrd {
VertexPostProcessor::VertexPostProcessor(const int width, const int height) : width_(width), height_(height) {
}

VertexOut VertexPostProcessor::Run(const VertexShaderOut &in) {
	vec3 ndc_position = PerspectiveDivide(in.clipping_position);
	vec3 window_position = ViewportTransform(ndc_position, width_, height_);
	VertexOut out;
	out.window_position = window_position;
	out.world_position = in.world_position;
	out.world_normal = in.world_normal;
	out.uv = in.uv;
	return out;
}


vec3 VertexPostProcessor::PerspectiveDivide(const vec4 &position) {
	return vec3(position.x / position.w, position.y / position.w, position.z / position.w);
}

vec3 VertexPostProcessor::ViewportTransform(const vec3 &position, int width, int height)
{
	float x = (width / 2.0) * (position.x + 1.0);
	float y = (height / 2.0) * (position.y + 1.0);
	float z = 0.5 * (position.z + 1.0);
	return vec3(x, y, z);
}


} // namespace softrd


