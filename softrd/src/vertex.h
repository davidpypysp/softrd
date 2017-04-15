#ifndef SOFTRD_VERTEX_H_
#define SOFTRD_VERTEX_H_

#include "math/vector.h"

namespace softrd {

// vertex contains position, normal, texutre_mapping...
struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;
};

} // namespace softrd

#endif // SOFTRD_VERTEX_H_
