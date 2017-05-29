#include "model.h"

#include <iostream>



namespace softrd {
Model::Model() {
}

Model::Model(const std::string &path) {
	LoadModel(path);
}

void Model::LoadTriangle() {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

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

	meshes.push_back(Mesh(vertices, indices));
}

void Model::LoadCube() {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

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
		vertices.push_back(vertex);
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
		indices.push_back(indices[i]);
	}

	meshes.push_back(Mesh(vertices, indices));
}

void Model::LoadCoordinateSystem() {
	Vertex v0, v1, v2, v3;
	v0.position = vec3(0.0, 0.0, 0.0); // origin
	v1.position = vec3(5.0, 0.0, 0.0); // x
	v2.position = vec3(0.0, 5.0, 0.0); // y
	v3.position = vec3(0.0, 0.0, 5.0); // z

	Mesh x;
	x.vertices.push_back(v0);
	x.vertices.push_back(v1);
	x.indices.push_back(0);
	x.indices.push_back(1);
	x.color = vec3(1.0, 0.0, 0.0);
	meshes.push_back(x);

	Mesh y;
	y.vertices.push_back(v0);
	y.vertices.push_back(v2);
	y.indices.push_back(0);
	y.indices.push_back(1);
	y.color = vec3(0.0, 1.0, 0.0);
	meshes.push_back(y);

	Mesh z;
	z.vertices.push_back(v0);
	z.vertices.push_back(v3);
	z.indices.push_back(0);
	z.indices.push_back(1);
	z.color = vec3(0.0, 0.0, 1.0);
	meshes.push_back(z);
}

void Model::LoadModel(const std::string &path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) { // if is Not Zero
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// Retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

bool Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	// for each vertex
	for (int i = 0; i < mesh->mNumVertices; i++) {

		Vertex vertex;
		vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0]) {
			vertex.uv = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		vertices.push_back(vertex);
	}

	// for each index
	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace &face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	meshes.push_back(Mesh(vertices, indices));
	return true;
}

} // namespace softrd


