#ifndef SOFTRD_MESH_H_
#define SOFTRD_MESH_H_

#include <vector>
#include <string>

#include "vertex.h"

namespace softrd {

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	vec3 color;

	Mesh() {
	}

	Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices) {
		this->vertices = vertices;
		this->indices = indices;
	}

	void LoadBuffer(std::vector<Vertex> &vertex_buffer, std::vector<uint32_t> &element_buffer) {
		vertex_buffer.clear();
		element_buffer.clear();

		for (Vertex &vertex : vertices) {
			vertex_buffer.push_back(vertex);
		}

		for (int element : indices) {
			element_buffer.push_back(element);
		}
	}

	void LoadLine(const vec3 &position0 = vec3(0, 0, 0), const vec3 &position1 = vec3(1.0, 0, 0), const vec3 &color = vec3(0, 0, 0)) {
		Vertex v0, v1;
		v0.position = position0;
		v1.position = position1;

		vertices.push_back(v0);
		vertices.push_back(v1);

		indices.push_back(0);
		indices.push_back(1);

		this->color = color;
	}

	void LoadTriangle() {
		Vertex v1, v2, v3;
		v1.position = vec3(-0.5, -0.5, 0);
		v2.position = vec3(0.5, 0.5, 0);
		v3.position = vec3(0.5, -0.5, 0);

		v1.uv = vec2(0.0, 1.0);
		v2.uv = vec2(1.0, 0.0);
		v3.uv = vec2(1.0, 1.0);

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

#define TRIANGLE2 0
#if TRIANGLE2
		Vertex v1, v2, v3, v4;
		v1.position = vec3(-0.5, 0.0, 0);
		v2.position = vec3(-0.5, 1.0, 0);
		v3.position = vec3(0.5, 0.0, 0);
		v4.position = vec3(0.5, 1.0, 0);

		v1.uv = vec2(0.0, 1.0);
		v2.uv = vec2(0.0, 0.0);
		v3.uv = vec2(1.0, 1.0);
		v4.uv = vec2(1.0, 0.0);

		vertex_buffer_.push_back(v1);
		vertex_buffer_.push_back(v2);
		vertex_buffer_.push_back(v3);
		vertex_buffer_.push_back(v4);

		element_buffer_.push_back(0);
		element_buffer_.push_back(1);
		element_buffer_.push_back(2);

		element_buffer_.push_back(1);
		element_buffer_.push_back(2);
		element_buffer_.push_back(3);

#endif
	}

	void LoadCube() {
		vec3 cube_positions[] = {
			vec3(0.5, -0.5, 0.5),
			vec3(0.5, 0.5, 0.5),
			vec3(-0.5, 0.5, 0.5),
			vec3(-0.5, -0.5, 0.5),

			vec3(0.5, -0.5, -0.5),
			vec3(0.5, 0.5, -0.5),
			vec3(-0.5, 0.5, -0.5),
			vec3(-0.5, -0.5, -0.5),
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
			vertices.push_back(vertex);
		}


		int elements[] = {
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
			indices.push_back(elements[i]);
		}
	}

};


} // namespace softrd

#endif // SOFTRD_MESH_H_