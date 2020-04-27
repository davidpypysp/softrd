#include "model.h"

#include <iostream>

namespace softrd {
Model::Model() { std::cout << "model constructor" << std::endl; }

Model::Model(const std::string &path) { LoadModel(path); }

void Model::LoadBuffer(std::vector<Vertex> &vertex_buffer,
                       std::vector<uint32_t> &element_buffer) {
  vertex_buffer.clear();
  element_buffer.clear();

  for (Mesh &mesh : meshes) {
    for (Vertex &vertex : mesh.vertices) {
      vertex_buffer.push_back(vertex);
    }

    for (int element : mesh.indices) {
      element_buffer.push_back(element);
    }
  }

  // Texture *texture = new Texture("resource/img_cheryl.jpg");
  // Texture *texture = new Texture("resource/mini.jpg");
  // Texture *texture = new Texture("resource/test_rect.png");
  // Texture *texture = new Texture("resource/container.jpg");
}

void Model::LoadLine(const math::vec3 &position0, const math::vec3 &position1,
                     const math::vec3 &color) {
  Mesh line;
  line.LoadLine(position0, position1, color);
  meshes.push_back(line);
}

void Model::LoadTriangle() {
  Mesh triangle;
  triangle.LoadTriangle();
  meshes.push_back(triangle);
}

void Model::LoadCube() {
  Mesh cube;
  cube.LoadCube();
  meshes.push_back(cube);
}

void Model::LoadCoordinateSystem() {
  Vertex v0, v1, v2, v3;
  v0.position = math::vec3(0.0, 0.0, 0.0);  // origin
  v1.position = math::vec3(5.0, 0.0, 0.0);  // x
  v2.position = math::vec3(0.0, 5.0, 0.0);  // y
  v3.position = math::vec3(0.0, 0.0, 5.0);  // z

  Mesh x;
  x.vertices.push_back(v0);
  x.vertices.push_back(v1);
  x.indices.push_back(0);
  x.indices.push_back(1);
  x.color = math::vec3(1.0, 0.0, 0.0);
  meshes.push_back(x);

  Mesh y;
  y.vertices.push_back(v0);
  y.vertices.push_back(v2);
  y.indices.push_back(0);
  y.indices.push_back(1);
  y.color = math::vec3(0.0, 1.0, 0.0);
  meshes.push_back(y);

  Mesh z;
  z.vertices.push_back(v0);
  z.vertices.push_back(v3);
  z.indices.push_back(0);
  z.indices.push_back(1);
  z.color = math::vec3(0.0, 0.0, 1.0);
  meshes.push_back(z);
}

void Model::LoadModel(const std::string &path) {
  Assimp::Importer importer;
  const aiScene *scene =
      importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {  // if is Not Zero
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
    vertex.position = math::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                                 mesh->mVertices[i].z);
    vertex.normal = math::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                               mesh->mNormals[i].z);
    if (mesh->mTextureCoords[0]) {
      vertex.uv = math::vec2(mesh->mTextureCoords[0][i].x,
                             mesh->mTextureCoords[0][i].y);
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

}  // namespace softrd
