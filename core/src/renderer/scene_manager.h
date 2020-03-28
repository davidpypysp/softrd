#ifndef SOFTRD_SCENE_MANAGER_H_
#define SOFTRD_SCENE_MANAGER_H_

#include <unordered_map>

#include "src/renderer/scene_object.h"

namespace softrd {
class SceneManager {
 public:
  SceneManager();

  std::shared_ptr<SceneObject> AddSceneObject(const std::string &id);
  std::shared_ptr<SceneObject> GetSceneObject(const std::string &id);

 private:
  std::unordered_map<std::string, std::shared_ptr<SceneObject>> scene_objects_;
};

}  // namespace softrd

#endif  // SOFTRD_SCENE_MANAGER_H_