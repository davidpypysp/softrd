#include "src/renderer/scene_manager.h"

namespace softrd {

SceneManager::SceneManager() {
  this->set_camera(std::make_shared<Camera>(float(640.0) / float(480.0)));
  this->InitShaders();
}

void SceneManager::InitShaders() {
  // vertex shaders
  auto vertex_shader_light = std::make_shared<VertexShaderLight>();
  vertex_shaders_.emplace(
      std::make_pair("vertex_shader_light", vertex_shader_light));

  // fragment shaders
  auto fragment_shader = std::make_shared<FragmentShader>();
  fragment_shaders_.emplace(std::make_pair("fragment_shader", fragment_shader));
}

std::shared_ptr<SceneObject> SceneManager::AddSceneObject(
    const std::string &id) {
  if (scene_objects_.find(id) == scene_objects_.end()) {
    return nullptr;
  }

  auto scene_object = std::make_shared<SceneObject>();
  scene_object->set_id(id);

  auto mesh = std::make_shared<Mesh>();
  mesh->LoadCube2();
  scene_object->set_mesh(mesh);

  auto vertex_shader_iterator = vertex_shaders_.find("vertex_shader_light");
  if (vertex_shader_iterator != vertex_shaders_.end()) {
    auto vertex_shader_light = vertex_shader_iterator->second;
    scene_object->set_vertex_shader(vertex_shader_light);
  }

  auto fragment_shader_iterator = fragment_shaders_.find("fragment_shader");
  if (fragment_shader_iterator != fragment_shaders_.end()) {
    auto fragment_shader = fragment_shader_iterator->second;
    scene_object->set_fragment_shader(fragment_shader);
  }

  auto material = std::make_shared<Material>(
      vec3(1.0, 1.0, 1.0), vec3(1.0, 0.5, 0.31), vec3(0.5, 0.5, 0.5), 32.0);
  scene_object->set_material(material);

  scene_objects_.emplace(std::make_pair(id, scene_object));

  return scene_object;
}

std::shared_ptr<SceneObject> SceneManager::GetSceneObject(
    const std::string &id) {
  const auto &iterator = scene_objects_.find(id);
  if (iterator == scene_objects_.end()) {
    return nullptr;
  }
  return iterator->second;
}

}  // namespace softrd