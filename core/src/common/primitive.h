#ifndef SOFTRD_PRIMITIVE_H_
#define SOFTRD_PRIMITIVE_H_

#include <vector>

#include "src/modules/vertex_shader.h"

namespace softrd {

struct Primitive {  // base class of all primitive class
  int size;
  std::vector<VertexOut> vertex_out;
};

struct LinePrimitive : public Primitive {  // line with 2 vertex
  LinePrimitive() {
    this->size = 2;
    this->vertex_out.resize(this->size);
  }
};

struct TrianglePrimitive : public Primitive {  // triangle with 3 vertex
  TrianglePrimitive() {
    size = 3;
    this->vertex_out.resize(this->size);
  }
};

}  // namespace softrd

#endif  // SOFTRD_PRIMITIVE_H_