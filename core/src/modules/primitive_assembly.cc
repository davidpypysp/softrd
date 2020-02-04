#include <array>

#include "src/modules/clipping.h"
#include "src/modules/primitive_assembly.h"

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
  check_elements_.Resize(vertex_num_);
  check_elements_.Empty();
  window_positions_.Resize(vertex_num_);
}

PrimitiveAssembler::~PrimitiveAssembler() {}

bool PrimitiveAssembler::AssembleLine(const int e1, const int e2,
                                      LinePrimitive *line) {
  int elements[] = {e1, e2};

  for (int i = 0; i < 2; ++i) {
    line->v[i] = vertex_out_buffer_[elements[i]];
  }

  if (Clipper::ClipLineNegativeW(line) == false) return false;
  if (Clipper::ClipLine(line) == false) return false;

  for (int i = 0; i < line->size; ++i) {
    vec4 position = line->v[i].position;

    // transform
    PerspectiveDivide(position);
    ViewportTransform(position, width_, height_);

    line->v[i].position = position;
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
    primitive.v[i] = vertex_out_buffer_[element];

    if (!check_elements_[element]) {
      vec4 position = primitive.v[i].position;

      // transform
      PerspectiveDivide(position);
      ViewportTransform(position, width_, height_);

      primitive.v[i].position = position;
      check_elements_[element] = true;
      window_positions_[element] = position;
    } else {
      primitive.v[i].position = window_positions_[element];
    }
  }
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

void PrimitiveAssembler::ViewportTransform(vec4 &position, const int width,
                                           const int height) {
  position.x = (width * 0.5) * (position.x + 1.0);
  position.y = (height * 0.5) *
               (-position.y + 1.0);  // the window space's zero is upside
  position.z = 0.5 * (position.z + 1.0);
}

}  // namespace softrd
