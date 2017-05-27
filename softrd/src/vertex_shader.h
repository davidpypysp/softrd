#ifndef SOFTRD_VERTEX_SHADER_H_
#define SOFTRD_VERTEX_SHADER_H_

#include "vertex.h"
#include "math/matrix.h"
#include "math/vector.h"

namespace softrd {

// contain clipping space position
struct VertexOut {
	vec4 position; // clipping space position
	vec3 world_position;
	vec3 world_normal;
	vec2 uv;
};

class VertexShader {
public:
	mat4 model_;
	mat4 view_;
	mat4 projection_;
	mat4 transform_;

	VertexShader();
	virtual bool Run(const Vertex &in, VertexOut *out);
};


class VertexShaderLight : public VertexShader {
	bool Run(const Vertex &in, VertexOut *out);
};


} // namespace softrd


#endif // SOFTRD_VERTEX_SHADER_H_