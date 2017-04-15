#ifndef SOFTRD_PRIMITIVE_ASSEMBLY_H_ 
#define SOFTRD_PRIMITIVE_ASSEMBLY_H_

#include <vector>

#include "vertex_shader.h"

namespace softrd {


struct TrianglePrimitive {
	VertexOut vertex[3];
};

class PrimitiveAssembler {
public:
	PrimitiveAssembler(const int width, const int height);
	std::vector<TrianglePrimitive> AssembleTriangle(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3);


private:

	bool Clip(const vec4 &position);
	bool PerspectiveDivide(vec4 &position); // clipping space position (x, y, z range in [-w, w]) -> normalized device coordinate(NDC) (x, y, z range in [-1, 1])
	void ViewportTransform(vec4 &position, int width, int height); // normalized device coordinate(NDC) -> window space coordinate (x - [0, width], y - [0, height], z - [0, 1])

	int width_, height_; // window space width and height
};

} // namespace softrd



#endif // SOFTRD_PRIMITIVE_ASSEMBLY_H_