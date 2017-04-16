#include "primitive_assembly.h"

namespace softrd {

PrimitiveAssembler::PrimitiveAssembler(const int width, const int height) : width_(width), height_(height) {
}

std::vector<TrianglePrimitive> PrimitiveAssembler::AssembleTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3) {
	std::vector<TrianglePrimitive> triangles;

	TrianglePrimitive triangle;
	triangle.vertex[0] = v1;
	triangle.vertex[1] = v2;
	triangle.vertex[2] = v3;
	

	// clipping
	for (int i = 0; i < 3; i++) {
		if (Clip(triangle.vertex[i].position)) return triangles;
	}
	
	for (int i = 0; i < 3; i++) {
		PerspectiveDivide(triangle.vertex[i].position);
		ViewportTransform(triangle.vertex[i].position, width_, height_);
	}
	triangles.push_back(triangle);

	return triangles;
}

bool PrimitiveAssembler::Clip(const vec4 &position) {
	return position.z < -position.w || position.z > position.w;
}

bool PrimitiveAssembler::PerspectiveDivide(vec4 &position) {
	if (position.w == 0) return false;
	position.x /= position.w;
	position.y /= position.w;
	position.z /= position.w;
	position.w = 1.0;
	return true;
}

void PrimitiveAssembler::ViewportTransform(vec4 &position, int width, int height) {
	position.x = (width / 2.0) * (position.x + 1.0);
	position.y = (height / 2.0) * (-position.y + 1.0);
	position.z = 0.5 * (position.z + 1.0);
}

} // namespace softrd


