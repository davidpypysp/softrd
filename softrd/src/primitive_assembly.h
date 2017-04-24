#ifndef SOFTRD_PRIMITIVE_ASSEMBLY_H_ 
#define SOFTRD_PRIMITIVE_ASSEMBLY_H_

#include <vector>

#include "vertex_shader.h"

namespace softrd {


struct TrianglePrimitive {
	VertexOut v[3];
};

class PrimitiveAssembler {
public:
	PrimitiveAssembler(const int width, const int height);
	void Setup(const int vertex_num, VertexOut *vertex_out_buffer);
	void Reset();
	~PrimitiveAssembler();
	
	bool AssembleTriangle(const int e1, const int e2, const int e3, std::vector<TrianglePrimitive> *triangles);


private:

	bool Clip(const vec4 &position);
	bool PerspectiveDivide(vec4 &position); // clipping space position (x, y, z range in [-w, w]) -> normalized device coordinate(NDC) (x, y, z range in [-1, 1])
	void ViewportTransform(vec4 &position, const int width, const int height); // normalized device coordinate(NDC) -> window space coordinate (x - [0, width], y - [0, height], z - [0, 1])

	int width_, height_; // window space width and height
	int vertex_num_;
	VertexOut *vertex_out_buffer_;
	bool *check_elements_;
	vec4 *window_positions_;
};

} // namespace softrd



#endif // SOFTRD_PRIMITIVE_ASSEMBLY_H_