#ifndef SOFTRD_PRIMITIVE_ASSEMBLY_H_ 
#define SOFTRD_PRIMITIVE_ASSEMBLY_H_

#include <vector>

#include "src/modules/vertex_shader.h"
#include "src/components/primitive.h"
#include "src/utils/util.h"

namespace softrd {


class PrimitiveAssembler {
public:
	PrimitiveAssembler(const int width, const int height, std::vector<VertexOut> &vertex_out_buffer);
	void Setup(std::vector<VertexOut> &vertex_out_buffer);
	void Reset();
	~PrimitiveAssembler();
	
	bool AssembleLine(const int e1, const int e2, LinePrimitive *line);
	bool AssembleTriangle(const int e1, const int e2, const int e3, std::vector<TrianglePrimitive> *triangles);
	bool GeneratePrimitive(int elements[], Primitive &primitive);


private:
	static bool PerspectiveDivide(vec4 &position); // clipping space position (x, y, z range in [-w, w]) -> normalized device coordinate(NDC) (x, y, z range in [-1, 1])
	static void ViewportTransform(vec4 &position, const int width, const int height); // normalized device coordinate(NDC) -> window space coordinate (x - [0, width], y - [0, height], z - [0, 1])

	int width_, height_; // window space width and height
	int vertex_num_;
	std::vector<VertexOut> &vertex_out_buffer_;
	util::Array<bool> check_elements_;
	//vec4 *window_positions_;
	util::Array<vec4> window_positions_;
};

} // namespace softrd



#endif // SOFTRD_PRIMITIVE_ASSEMBLY_H_