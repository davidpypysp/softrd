#include "src/renderer/scene_manager.h"

namespace softrd {

SceneManager::SceneManager() {}

std::shared_ptr<SceneObject> SceneManager::AddSceneObject(
    const std::string &id) {
  if (scene_objects_.find(id) == scene_objects_.end()) {
    return nullptr;
  }

  auto scene_object = std::make_shared<SceneObject>();
  scene_object->set_id(id);

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