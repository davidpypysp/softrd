#ifndef SOFTRD_MODEL_H_
#define SOFTRD_MODEL_H_

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"


namespace softrd {

class Model {
public:
	Model(const std::string &path);
	void Draw();

	std::vector<Mesh> meshes_;

private:

	void LoadModel(const std::string &path);
	void ProcessNode(aiNode *node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);


	std::string directory_;

};

} // namespace softrd


#endif // SOFTRD_MODEL_H_