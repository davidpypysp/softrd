#include "primitive_assembly.h"

namespace softrd {

PrimitiveAssembler::PrimitiveAssembler() {
}

TrianglePrimitive PrimitiveAssembler::AssembleTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3) {
	TrianglePrimitive triangle;
	triangle.vertex[0] = v1;
	triangle.vertex[1] = v2;
	triangle.vertex[2] = v3;
	return triangle;
}

} // namespace softrd


