#ifndef SOFTRD_PRIMITIVE_H_
#define SOFTRD_PRIMITIVE_H_

#include "src/modules/vertex_shader.h"

namespace softrd {

struct Primitive { // base class of all primitive class
	VertexOut *v;
	int size;
};

struct LinePrimitive : public Primitive { // line with 2 vertex
	LinePrimitive() {
		size = 2;
		v = new VertexOut[size];
	}
};

struct TrianglePrimitive : public Primitive { // triangle with 3 vertex
	TrianglePrimitive() {
		size = 3;
		v = new VertexOut[size];
	}
};

} // namespace softrd


#endif // SOFTRD_PRIMITIVE_H_