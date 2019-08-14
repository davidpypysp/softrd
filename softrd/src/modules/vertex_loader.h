#ifndef VERTEX_LOADER_H_
#define VERTEX_LOADER_H_

#include <vector>
#include "vertex.h"
namespace softrd {

class VertexLoader {
public:
	VertexLoader(std::vector<Vertex> *vertex_buffer = nullptr, std::vector<uint32_t> *element_buffer = nullptr);
	void Setup(std::vector<Vertex> *vertex_buffer, std::vector<uint32_t> *element_buffer);
	void LoadCube();
	void LoadTriangle();
	void LoadCoordinateSystem();

private:
	std::vector<Vertex> *vertex_buffer_;
	std::vector<uint32_t> *element_buffer_;
};

} // namespace softrd

#endif // VERTEX_LOADER_H_