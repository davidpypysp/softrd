#include "src/renderer/scene_manager.h"

namespace softrd {

SceneManager::SceneManager() {
  this->set_default_camera(
      std::make_shared<scene::Camera>(math::vec3(6, 6, 9), 640.0 / 480.0));

  this->InitShaders();

  // this->AddExampleObjects();
}

void SceneManager::InitShaders() {
  // vertex shaders
  auto vertex_shader_light = std::make_shared<VertexShaderLight>();
  vertex_shaders_.emplace(
      std::make_pair("vertex_shader_light", vertex_shader_light));

  // fragment shaders
  auto fragment_shader = std::make_shared<FragmentShader>();
  fragment_shaders_.emplace(std::make_pair("fragment_shader", fragment_shader));

  auto material = std::make_shared<Material>(math::vec3(1.0, 1.0, 1.0),
                                             math::vec3(1.0, 0.5, 0.31),
                                             math::vec3(0.5, 0.5, 0.5), 32.0);
  auto fragment_shader_light_full = std::make_shared<FragmentShaderLightFull>(
      default_camera_->PositionPtr(), material);
  SpotLight *spot_light =
      new SpotLight(math::vec3(3.0, 0.0, 0.0), math::vec3(-1.0, 0.0, 0.0),
                    cos(math::Radians(12.5)), cos(math::Radians(17.5)),
                    math::vec3(0.1, 0.1, 0.1), math::vec3(0.8, 0.8, 0.8),
                    math::vec3(1.0, 1.0, 1.0), 1.0, 0.09, 0.032);
  fragment_shader_light_full->AddLight(spot_light);
  fragment_shaders_.emplace(
      std::make_pair("fragment_shader_light_full", fragment_shader_light_full));
}

void SceneManager::AddExampleObjects() {
  this->AddSpotLightObject("TestSpotLight", math::vec3(4.0, 0.0, 0.0),
                           math::vec3(-1.0, 0.0, 0.0));
  this->AddSceneObject("TestCube");
  // this->AddSceneObject("TestCube2", math::vec3(3, 0, 1));
}

std::shared_ptr<scene::SceneObject> SceneManager::AddSceneObject(
    const std::string &id, const math::vec3 &position,
    const math::vec3 &rotation) {
  if (scene_objects_.find(id) != scene_objects_.end()) {
    return nullptr;
  }

  auto scene_object = std::make_shared<scene::SceneObject>();
  scene_object->set_id(id);

  auto mesh = std::make_shared<Mesh>();
  mesh->LoadCube2();
  scene_object->set_mesh(mesh);

  auto vertex_shader_iterator = vertex_shaders_.find("vertex_shader_light");
  if (vertex_shader_iterator != vertex_shaders_.end()) {
    auto vertex_shader_light = vertex_shader_iterator->second;
    scene_object->set_vertex_shader(vertex_shader_light);
  }

  auto fragment_shader_iterator =
      fragment_shaders_.find("fragment_shader_light_full");
  if (fragment_shader_iterator != fragment_shaders_.end()) {
    auto fragment_shader = fragment_shader_iterator->second;
    scene_object->set_fragment_shader(fragment_shader);
  }

  auto material = std::make_shared<Material>(math::vec3(1.0, 1.0, 1.0),
                                             math::vec3(1.0, 0.5, 0.31),
                                             math::vec3(0.5, 0.5, 0.5), 32.0);
  scene_object->set_material(material);

  scene_object->set_position(position);
  scene_object->set_rotation(rotation);
  scene_object->set_scale(math::vec3(1, 1, 1));

  scene_objects_.emplace(std::make_pair(id, scene_object));

  return scene_object;
}

std::shared_ptr<scene::SpotLightObject> SceneManager::AddSpotLightObject(
    const std::string &id, const math::vec3 &position,
    const math::vec3 &rotation) {
  if (scene_objects_.find(id) != scene_objects_.end()) {
    return nullptr;
  }

  auto spot_light_object = std::make_shared<scene::SpotLightObject>();
  spot_light_object->set_id(id);

  auto mesh = std::make_shared<Mesh>();
  mesh->LoadCube();
  spot_light_object->set_mesh(mesh);

  auto vertex_shader_iterator = vertex_shaders_.find("vertex_shader_light");
  if (vertex_shader_iterator != vertex_shaders_.end()) {
    auto vertex_shader_light = vertex_shader_iterator->second;
    spot_light_object->set_vertex_shader(vertex_shader_light);
  }

  auto fragment_shader_iterator = fragment_shaders_.find("fragment_shader");
  if (fragment_shader_iterator != fragment_shaders_.end()) {
    auto fragment_shader = fragment_shader_iterator->second;
    spot_light_object->set_fragment_shader(fragment_shader);
  }

  spot_light_object->set_position(position);
  spot_light_object->set_rotation(rotation);
  spot_light_object->set_scale(math::vec3(0.1, 0.1, 0.1));

  scene_objects_.emplace(std::make_pair(id, spot_light_object));

  return spot_light_object;
}

std::shared_ptr<scene::SceneObject> SceneManager::GetSceneObject(
    const std::string &id) {
  const auto &iterator = scene_objects_.find(id);
  if (iterator == scene_objects_.end()) {
    return nullptr;
  }
  return iterator->second;
}

}  // namespace softrd