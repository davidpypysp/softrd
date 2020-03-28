#ifndef SOFTRD_SCENE_MANAGER_H_
#define SOFTRD_SCENE_MANAGER_H_

#include <unordered_map>

#include "src/renderer/scene_object.h"

namespace softrd {
class SceneManager {
 public:
  SceneManager();

 private:
  std::unordered_map<std::string, std::shared_ptr<SceneObject>> scene_objects_;
};

}  // namespace softrd

#endif  // SOFTRD_SCENE_MANAGER_H_