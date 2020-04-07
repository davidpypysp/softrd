#ifndef SOFTRD_SCENE_MANAGER_H_
#define SOFTRD_SCENE_MANAGER_H_

#include <unordered_map>

#include "src/components/camera.h"
#include "src/renderer/scene_object.h"

namespace softrd {
class SceneManager {
 public:
  SceneManager();

  void InitShaders();
  void AddExampleObjects();

  std::shared_ptr<SceneObject> AddSceneObject(
      const std::string &id, const vec3 &position = vec3(0, 0, 0),
      const vec3 &rotation = vec3(0, 0, 0));
  std::shared_ptr<SpotLightObject> AddSpotLightObject(
      const std::string &id, const vec3 &position = vec3(0, 0, 0),
      const vec3 &rotation = vec3(0, 0, 0));
  std::shared_ptr<SceneObject> GetSceneObject(const std::string &id);

  void set_camera(const std::shared_ptr<Camera> &camera) { camera_ = camera; }
  std::shared_ptr<Camera> camera() const { return camera_; }

  std::unordered_map<std::string, std::shared_ptr<SceneObject>> scene_objects()
      const {
    return scene_objects_;
  }

 private:
  std::unordered_map<std::string, std::shared_ptr<SceneObject>> scene_objects_;

  std::unordered_map<std::string, std::shared_ptr<VertexShader>>
      vertex_shaders_;
  std::unordered_map<std::string, std::shared_ptr<FragmentShader>>
      fragment_shaders_;

  std::shared_ptr<Camera> camera_;
};

}  // namespace softrd

#endif  // SOFTRD_SCENE_MANAGER_H_