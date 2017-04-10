#ifndef SOFTRD_PRIMITIVE_ASSEMBLY_H_ 
#define SOFTRD_PRIMITIVE_ASSEMBLY_H_

#include "vertex_post_processing.h"

namespace softrd {

struct TrianglePrimitive {
	VertexOut vertex[3];
};

class PrimitiveAssembler {
public:
	PrimitiveAssembler();
	TrianglePrimitive AssembleTriangle(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3);


private:
};

} // namespace softrd



#endif // SOFTRD_PRIMITIVE_ASSEMBLY_H_