#ifndef SOFTRD_MODEL_H_
#define SOFTRD_MODEL_H_

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <string>

#include "src/common/mesh.h"

namespace softrd {

struct Model {
  std::vector<Mesh> meshes;
  std::string directory;

  Model();
  Model(const std::string &path);
  void LoadBuffer(std::vector<Vertex> &vertex_buffer,
                  std::vector<uint32_t> &element_buffer);
  void Draw();

  void LoadLine(const math::vec3 &position0 = math::vec3(0, 0, 0),
                const math::vec3 &position1 = math::vec3(1.0, 0, 0),
                const math::vec3 &color = math::vec3(0, 0, 0));
  void LoadTriangle();
  void LoadCube();
  void LoadCoordinateSystem();
  void LoadModel(const std::string &path);
  void ProcessNode(aiNode *node, const aiScene *scene);
  bool ProcessMesh(aiMesh *mesh, const aiScene *scene);
};

}  // namespace softrd

#endif  // SOFTRD_MODEL_H_