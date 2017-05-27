#include "vertex_loader.h"


namespace softrd {

VertexLoader::VertexLoader() {
}

void VertexLoader::LoadCube(std::vector<Vertex> &vertex_buffer, std::vector<uint32_t> &element_buffer) {
	vec3 cube_positions[] = {
		vec3(0.5, -0.5, 0.0),
		vec3(0.5, 0.5, 0.0),
		vec3(-0.5, 0.5, 0.0),
		vec3(-0.5, -0.5, 0.0),

		vec3(0.5, -0.5, -1.0),
		vec3(0.5, 0.5, -1.0),
		vec3(-0.5, 0.5, -1.0),
		vec3(-0.5, -0.5, -1.0),
	};

	vec2 cube_uvs[] = {
		vec2(1.0, 1.0),
		vec2(1.0, 0.0),
		vec2(0.0, 0.0),
		vec2(0.0, 1.0),

		vec2(0.0, 1.0),
		vec2(0.0, 0.0),
		vec2(1.0, 0.0),
		vec2(1.0, 1.0)
	};

	for (int i = 0; i < 8; i++) {
		Vertex vertex;
		vertex.position = cube_positions[i];
		vertex.uv = cube_uvs[i];
		vertex_buffer.push_back(vertex);
	}


	int indices[] = {
		0, 1, 3, // front
		1, 2, 3,

		4, 5, 0, // right
		5, 1, 0,

		4, 0, 7, // down
		0, 3, 7,

		1, 5, 2, // up
		5, 6, 2,

		3, 2, 7, // left
		2, 6, 7,

		7, 6, 4, // back
		6, 5, 4
	};
	for (int i = 0; i < 36; i++) {
		element_buffer.push_back(indices[i]);
	}
}

void VertexLoader::LoadTriangle(std::vector<Vertex>& vertex_buffer, std::vector<uint32_t>& element_buffer) {
	Vertex v1, v2, v3;
	v1.position = vec3(-0.5, -0.5, 0);
	v2.position = vec3(0.5, 0.5, 0);
	v3.position = vec3(0.5, -0.5, 0);

	v1.uv = vec2(0.0, 1.0);
	v2.uv = vec2(1.0, 0.0);
	v3.uv = vec2(1.0, 1.0);

	vertex_buffer.push_back(v1);
	vertex_buffer.push_back(v2);
	vertex_buffer.push_back(v3);

	element_buffer.push_back(0);
	element_buffer.push_back(1);
	element_buffer.push_back(2);
}


}


