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
	void Draw();

	void LoadTriangle();
	void LoadCube();
	void LoadCoordinateSystem();
	void LoadModel(const std::string &path);
	void ProcessNode(aiNode *node, const aiScene* scene);
	bool ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

} // namespace softrd


#endif // SOFTRD_MODEL_H_