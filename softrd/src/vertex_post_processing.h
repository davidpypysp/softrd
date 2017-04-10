#ifndef SOFTRD_VERTEX_POST_PROCESSING_H_
#define SOFTRD_VERTEX_POST_PROCESSING_H_

#include "math/vector.h"
#include "vertex_shader.h"

// vertex post processing:
// clipping(skip for now)
// perspective divide
// viewport transform


namespace softrd {

// contains window space position
struct VertexOut {
	vec3 window_position;
	vec3 world_position;
	vec3 world_normal;
	vec2 uv;
};

class VertexPostProcessor {
public:
	VertexPostProcessor(const int width, const int height);
	VertexOut Run(const VertexShaderOut &in);

private:
	vec3 PerspectiveDivide(const vec4 &position); // clipping space position (x, y, z range in [-w, w]) -> normalized device coordinate(NDC) (x, y, z range in [-1, 1])
	vec3 ViewportTransform(const vec3 &position, int width, int height); // normalized device coordinate(NDC) -> window space coordinate (x - [0, width], y - [0, height], z - [0, 1])

	int width_, height_; // window space width and height
};








} // namespace softrd


#endif // SOFTRD_VERTEX_POST_PROCESSING_H_