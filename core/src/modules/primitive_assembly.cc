#include "src/modules/primitive_assembly.h"

#include <array>

#include "src/modules/clipping.h"

namespace softrd {

PrimitiveAssembler::PrimitiveAssembler(
    const int width, const int height,
    std::vector<VertexOut> &vertex_out_buffer)
    : width_(width), height_(height), vertex_out_buffer_(vertex_out_buffer) {}

void PrimitiveAssembler::Setup(std::vector<VertexOut> &vertex_out_buffer) {
  vertex_out_buffer_ = vertex_out_buffer;
}

void PrimitiveAssembler::Reset() {
  vertex_num_ = vertex_out_buffer_.size();
  checked_elements_.resize(vertex_num_);
  std::fill(checked_elements_.begin(), checked_elements_.end(), false);
  window_positions_.resize(vertex_num_);
}

PrimitiveAssembler::~PrimitiveAssembler() {}

bool PrimitiveAssembler::AssembleLine(const int e1, const int e2,
                                      LinePrimitive *line) {
  int elements[] = {e1, e2};

  for (int i = 0; i < 2; ++i) {
    line->vertex_out[i] = vertex_out_buffer_[elements[i]];
  }

  if (Clipper::ClipLineNegativeW(line) == false) return false;
  if (Clipper::ClipLine(line) == false) return false;

  for (int i = 0; i < line->size; ++i) {
    math::vec4 position = line->vertex_out[i].position;

    // transform
    PerspectiveDivide(position);
    ViewportTransform(position, width_, height_);

    line->vertex_out[i].position = position;
  }

  return true;
}

bool PrimitiveAssembler::AssembleTriangle(
    const int e1, const int e2, const int e3,
    std::vector<TrianglePrimitive> *triangles) {
  int elements[] = {e1, e2, e3};

  // clipping
  for (int i = 0; i < 3; ++i) {
    if (Clipper::OutsideViewFrustum(vertex_out_buffer_[elements[i]].position)) {
      return false;
    }
  }
  TrianglePrimitive triangle;
  GeneratePrimitive(elements, triangle);
  triangles->push_back(triangle);

  return true;
}

bool PrimitiveAssembler::GeneratePrimitive(int elements[],
                                           Primitive &primitive) {
  for (int i = 0; i < primitive.size; ++i) {
    int element = elements[i];
    primitive.vertex_out[i] = vertex_out_buffer_[element];

    if (!checked_elements_[element]) {
      math::vec4 position = primitive.vertex_out[i].position;

      // transform
      PerspectiveDivide(position);
      ViewportTransform(position, width_, height_);

      primitive.vertex_out[i].position = position;
      checked_elements_[element] = true;
      window_positions_[element] = position;
    } else {
      primitive.vertex_out[i].position = window_positions_[element];
    }
  }
  return true;
}

bool PrimitiveAssembler::PerspectiveDivide(math::vec4 &position) {
  if (position.w == 0) return false;
  position.x /= position.w;
  position.y /= position.w;
  position.z /= position.w;
  position.w = 1.0;
  return true;
}

void PrimitiveAssembler::ViewportTransform(math::vec4 &position,
                                           const int width, const int height) {
  position.x = (width * 0.5) * (position.x + 1.0);
  position.y = (height * 0.5) *
               (-position.y + 1.0);  // the window space's zero is upside
  position.z = 0.5 * (position.z + 1.0);
}

}  // namespace softrd
