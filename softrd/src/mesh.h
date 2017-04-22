#ifndef SOFTRD_MESH_H_
#define SOFTRD_MESH_H_

#include <vector>
#include <string>

#include "vertex.h"

namespace softrd {

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices) {
		this->vertices = vertices;
		this->indices = indices;
	}

};


} // namespace softrd

#endif // SOFTRD_MESH_H_