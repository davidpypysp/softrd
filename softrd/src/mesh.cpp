#include "mesh.h"

namespace softrd {

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices) : 
vertices_(vertices),
indices_(indices) {
	Setup();
}

void Mesh::Setup() {
}


} // namespace softrd

