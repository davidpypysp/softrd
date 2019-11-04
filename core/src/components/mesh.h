#ifndef SOFTRD_MESH_H_
#define SOFTRD_MESH_H_

#include <vector>
#include <string>

#include "src/components/vertex.h"

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

		v1.normal = vec3(0, 0, 1.0);
		v2.normal = vec3(0, 0, 1.0);
		v3.normal = vec3(0, 0, 1.0);

		v1.uv = vec2(0.0, 1.0); // left, down
		v2.uv = vec2(1.0, 0.0); // right, up
		v3.uv = vec2(1.0, 1.0); // right, down

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

	void LoadSquare() {
		Vertex data[] = {
			Vertex(vec3(-1.0, -1.0, 0), vec3(0, 0, 1), vec2(0.0, 1.0)),
			Vertex(vec3(1.0, -1.0, 0), vec3(0, 0, 1), vec2(1.0, 1.0)),
			Vertex(vec3(-1.0, 1.0, 0), vec3(0, 0, 1), vec2(0.0, 0.0)),

			Vertex(vec3(-1.0, 1.0, 0), vec3(0, 0, 1), vec2(0.0, 0.0)),
			Vertex(vec3(1.0, -1.0, 0), vec3(0, 0, 1), vec2(1.0, 1.0)),
			Vertex(vec3(1.0, 1.0, 0), vec3(0, 0, 1), vec2(1.0, 0.0)),
		};
		
		for (int i = 0; i < 6; ++i) {
			vertices.push_back(data[i]);
			indices.push_back(i);
		}
	}

	void LoadCube() {
		vec3 positions[] = {
			vec3(0.5, -0.5, 0.5),
			vec3(0.5, 0.5, 0.5),
			vec3(-0.5, 0.5, 0.5),
			vec3(-0.5, -0.5, 0.5),

			vec3(0.5, -0.5, -0.5),
			vec3(0.5, 0.5, -0.5),
			vec3(-0.5, 0.5, -0.5),
			vec3(-0.5, -0.5, -0.5),
		};

		vec2 uvs[] = {
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
			vertex.position = positions[i];
			vertex.uv = uvs[i];
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

	void LoadCube2() {
		float data[] = {
			// positions       // normals        // texture coords
			-0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  0.0,  1.0,  // front
			0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  1.0,  1.0,
			0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  1.0,  0.0,
			0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  1.0,  0.0,
			-0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  0.0,  0.0,
			-0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  0.0,  1.0,

			-0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  1.0,  1.0,  // back
			0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  0.0,  1.0,
			0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  0.0,  0.0,
			0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  0.0,  0.0,
			-0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  1.0,  0.0,
			-0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  1.0,  1.0,


			-0.5,  0.5,  0.5, -1.0,  0.0,  0.0,  1.0,  0.0, // left
			-0.5,  0.5, -0.5, -1.0,  0.0,  0.0,  0.0,  0.0,
			-0.5, -0.5, -0.5, -1.0,  0.0,  0.0,  0.0,  1.0,
			-0.5, -0.5, -0.5, -1.0,  0.0,  0.0,  0.0,  1.0,
			-0.5, -0.5,  0.5, -1.0,  0.0,  0.0,  1.0,  1.0,
			-0.5,  0.5,  0.5, -1.0,  0.0,  0.0,  1.0,  0.0,

			0.5,  0.5,  0.5,  1.0,  0.0,  0.0,  0.0,  0.0, // right
			0.5,  0.5, -0.5,  1.0,  0.0,  0.0,  1.0,  0.0,
			0.5, -0.5, -0.5,  1.0,  0.0,  0.0,  1.0,  1.0,
			0.5, -0.5, -0.5,  1.0,  0.0,  0.0,  1.0,  1.0,
			0.5, -0.5,  0.5,  1.0,  0.0,  0.0,  0.0,  1.0,
			0.5,  0.5,  0.5,  1.0,  0.0,  0.0,  0.0,  0.0,

			-0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  0.0,  1.0, // down
			0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  1.0,  1.0,
			0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  1.0,  0.0,
			0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  1.0,  0.0,
			-0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  0.0,  0.0,
			-0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  0.0,  1.0,

			-0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  0.0,  0.0, // up
			0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  1.0,  0.0,
			0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  1.0,  1.0,
			0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  1.0,  1.0,
			-0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  0.0,  1.0,
			-0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  0.0,  0.0
		};

		for (int i = 0; i < 36; ++i) {
			Vertex vertex;
			vertex.position = vec3(data[i * 8], data[i * 8 + 1], data[i * 8 + 2]);
			vertex.normal = vec3(data[i * 8 + 3], data[i * 8 + 4], data[i * 8 + 5]);
			vertex.uv = vec2(data[i * 8 + 6], data[i * 8 + 7]);
			vertices.push_back(vertex);
			indices.push_back(i);
		}
	}

};


} // namespace softrd

#endif // SOFTRD_MESH_H_