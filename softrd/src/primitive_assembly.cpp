#include "primitive_assembly.h"
#include <array>

namespace softrd {

PrimitiveAssembler::PrimitiveAssembler(const int width, const int height, std::vector<VertexOut> &vertex_out_buffer) : 
	width_(width), 
	height_(height),
	vertex_out_buffer_(vertex_out_buffer) {
}

void PrimitiveAssembler::Setup(std::vector<VertexOut> &vertex_out_buffer) {
	vertex_out_buffer_ = vertex_out_buffer;

}

void PrimitiveAssembler::Reset() {
	delete[] check_elements_;
	delete[] window_positions_;

	vertex_num_ = vertex_out_buffer_.size();
	check_elements_ = new bool[vertex_num_];
	memset(check_elements_, 0, sizeof(bool) * vertex_num_);
	window_positions_ = new vec4[vertex_num_];
}

PrimitiveAssembler::~PrimitiveAssembler() {
	delete[] check_elements_;
	delete[] window_positions_;
}

bool PrimitiveAssembler::AssembleLine(const int e1, const int e2, LinePrimitive *line) {
	int elements[] = { e1, e2 };
	
	
	for (int i = 0; i < 2; ++i) {
		if (Clip(vertex_out_buffer_[elements[i]].position)) return false;
	}
	
	
	GeneratePrimitive(elements, *line);
	return true;
}

bool PrimitiveAssembler::AssembleTriangle(const int e1, const int e2, const int e3, std::vector<TrianglePrimitive> *triangles) {

	int elements[] = { e1, e2, e3 };

	// clipping
	for (int i = 0; i < 3; ++i) {
		if (Clip(vertex_out_buffer_[elements[i]].position)) return false;
	}
	TrianglePrimitive triangle;
	GeneratePrimitive(elements, triangle);
	triangles->push_back(triangle);

	return true;
}

bool PrimitiveAssembler::GeneratePrimitive(int elements[], Primitive &primitive) {
	for (int i = 0; i < primitive.size; ++i) {
		int element = elements[i];
		primitive.v[i] = vertex_out_buffer_[element];

		if (!check_elements_[element]) {
			vec4 position = primitive.v[i].position;

			// transform 
			PerspectiveDivide(position);
			ViewportTransform(position, width_, height_);

			primitive.v[i].position = position;
			check_elements_[element] = true;
			window_positions_[element] = position;
		}
		else {
			primitive.v[i].position = window_positions_[element];
		}
	}
	return true;
}

bool PrimitiveAssembler::Clip(const vec4 &position) { // position out of frustum
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


