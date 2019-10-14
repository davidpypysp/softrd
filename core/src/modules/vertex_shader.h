#ifndef SOFTRD_VERTEX_SHADER_H_
#define SOFTRD_VERTEX_SHADER_H_

#include "src/math/vector.h"
#include "src/math/matrix.h"
#include "src/components/vertex.h"

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

	mat4 transform_;

	VertexShader();
	bool Run(const Vertex &in, VertexOut *out);
	virtual bool Program();

	Vertex in_;
	VertexOut *out_;
};


class VertexShaderLight : public VertexShader {
public:
	mat4 model_;
	mat4 view_;
	mat4 projection_;

	bool Program();

};


} // namespace softrd


#endif // SOFTRD_VERTEX_SHADER_H_