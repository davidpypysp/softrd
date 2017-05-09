#include "primitive_assembly.h"

namespace softrd {

PrimitiveAssembler::PrimitiveAssembler(const int width, const int height) : width_(width), height_(height) {
}

void PrimitiveAssembler::Setup(const int vertex_num, VertexOut *vertex_out_buffer) {
	vertex_num_ = vertex_num;
	vertex_out_buffer_ = vertex_out_buffer;
	check_elements_ = new bool[vertex_num_];
	window_positions_ = new vec4[vertex_num_];
}

void PrimitiveAssembler::Reset() {
	memset(check_elements_, 0, sizeof(bool) * vertex_num_);
}

PrimitiveAssembler::~PrimitiveAssembler() {
	delete[] check_elements_;
	delete[] window_positions_;
}

bool PrimitiveAssembler::AssembleTriangle(const int e1, const int e2, const int e3, std::vector<TrianglePrimitive> *triangles) {

	int elements[] = { e1, e2, e3 };

	// clipping
	for (int i = 0; i < 3; i++) {
		if (Clip(vertex_out_buffer_[elements[i]].position)) return false;
	}
	TrianglePrimitive triangle;
	for (int i = 0; i < 3; i++) {
		int element = elements[i];
		triangle.v[i] = vertex_out_buffer_[element];

		if (!check_elements_[element]) {
			vec4 position = triangle.v[i].position;

			// transform 
			PerspectiveDivide(position);
			ViewportTransform(position, width_, height_);

			triangle.v[i].position = position;
			check_elements_[element] = true;
			window_positions_[element] = position;
		}
		else {
			triangle.v[i].position = window_positions_[element];
		}
	}
	triangles->push_back(triangle);

	return true;
}

bool PrimitiveAssembler::Clip(const vec4 &position) {
	if (position.x >= -position.w && position.x <= position.w) return false;
	if (position.y >= -position.w && position.y <= position.w) return false;
	if (position.z >= -position.w && position.z <= position.w) return false;
	return true;
}

bool PrimitiveAssembler::PerspectiveDivide(vec4 &position) {
	if (position.w == 0) return false;
	position.x /= position.w;
	position.y /= position.w;
	position.z /= position.w;
	position.w = 1.0;
	return true;
}

void PrimitiveAssembler::ViewportTransform(vec4 &position, const int width, const int height) {
	position.x = (width * 0.5) * (position.x + 1.0);
	position.y = (height * 0.5) * (-position.y + 1.0); // the window space's zero is upside
	position.z = 0.5 * (position.z + 1.0);
}

} // namespace softrd


