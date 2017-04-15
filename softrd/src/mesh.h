#ifndef SOFTRD_MESH_H_
#define SOFTRD_MESH_H_

#include <vector>
#include <string>

#include "vertex.h"

namespace softrd {

class Mesh {
public:
	std::vector<Vertex> vertices_;
	std::vector<uint32_t> indices_;

	Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
	void Draw();

private:
	void Setup();

};


} // namespace softrd

#endif // SOFTRD_MESH_H_