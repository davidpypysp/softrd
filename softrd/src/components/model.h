#ifndef SOFTRD_MODEL_H_
#define SOFTRD_MODEL_H_

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"


namespace softrd {

struct Model {

	std::vector<Mesh> meshes;
	std::string directory;
	
	Model();
	Model(const std::string &path);
	void LoadBuffer(std::vector<Vertex> &vertex_buffer, std::vector<uint32_t> &element_buffer);
	void Draw();

	void LoadLine(const vec3 &position0 = vec3(0, 0, 0), const vec3 &position1 = vec3(1.0, 0, 0), const vec3 &color = vec3(0, 0, 0));
	void LoadTriangle();
	void LoadCube();
	void LoadCoordinateSystem();
	void LoadModel(const std::string &path);
	void ProcessNode(aiNode *node, const aiScene* scene);
	bool ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

} // namespace softrd


#endif // SOFTRD_MODEL_H_