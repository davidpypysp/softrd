#ifndef SOFTRD_VERTEX_H_
#define SOFTRD_VERTEX_H_

#include "src/math/vector.h"

namespace softrd {

// vertex contains position, normal, texutre_mapping...
struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;

	Vertex(const vec3 &position = vec3(), const vec3 &normal = vec3(), const vec2 &uv = vec2()) :
		position(position),
		normal(normal),
		uv(uv) {
	}
};

} // namespace softrd

#endif // SOFTRD_VERTEX_H_
