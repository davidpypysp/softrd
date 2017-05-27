#ifndef VERTEX_LOADER_H_
#define VERTEX_LOADER_H_

#include <vector>
#include "vertex.h"
namespace softrd {

class VertexLoader {
public:
	VertexLoader();
	void LoadCube(std::vector<Vertex> &vertex_buffer, std::vector<uint32_t> &element_buffer);
	void LoadTriangle(std::vector<Vertex> &vertex_buffer, std::vector<uint32_t> &element_buffer);

private:
};

} // namespace softrd

#endif // VERTEX_LOADER_H_