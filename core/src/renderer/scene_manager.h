#ifndef SOFTRD_SCENE_MANAGER_H_
#define SOFTRD_SCENE_MANAGER_H_

#include <unordered_map>

#include "src/scene/scene_object.h"
#include "src/scene/camera.h"

namespace softrd {
class SceneManager {
 public:
  SceneManager();

  void InitShaders();
  void AddExampleObjects();

  std::shared_ptr<scene::SceneObject> AddSceneObject(
      const std::string &id, const math::vec3 &position = math::vec3(0, 0, 0),
      const math::vec3 &rotation = math::vec3(0, 0, 0));
  std::shared_ptr<scene::SpotLightObject> AddSpotLightObject(
      const std::string &id, const math::vec3 &position = math::vec3(0, 0, 0),
      const math::vec3 &rotation = math::vec3(0, 0, 0));
  std::shared_ptr<scene::SceneObject> GetSceneObject(const std::string &id);

  void set_default_camera(const std::shared_ptr<scene::Camera> &camera) {
    default_camera_ = camera;
  }
  std::shared_ptr<scene::Camera> default_camera() const { return default_camera_; }

  std::unordered_map<std::string, std::shared_ptr<scene::SceneObject>> scene_objects()
      const {
    return scene_objects_;
  }

 private:
  std::unordered_map<std::string, std::shared_ptr<scene::SceneObject>> scene_objects_;

  std::unordered_map<std::string, std::shared_ptr<VertexShader>>
      vertex_shaders_;
  std::unordered_map<std::string, std::shared_ptr<FragmentShader>>
      fragment_shaders_;

  std::shared_ptr<scene::Camera> default_camera_;
};

}  // namespace softrd

#endif  // SOFTRD_SCENE_MANAGER_H_