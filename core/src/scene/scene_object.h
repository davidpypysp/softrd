#ifndef SOFTRD_SCENE_OBJECT_H_
#define SOFTRD_SCENE_OBJECT_H_

#include <memory>

#include "src/scene/base_object.h"
#include "src/common/mesh.h"
#include "src/modules/fragment_shader.h"
#include "src/modules/vertex_shader.h"

namespace softrd {

namespace scene {

class SceneObject : public BaseObject {
 public:
  void set_scale(const math::vec3 &scale) { scale_ = scale; }
  math::vec3 scale() const { return scale_; }

  void set_mesh(const std::shared_ptr<Mesh> &mesh) { mesh_ = mesh; }
  std::shared_ptr<Mesh> mesh() const { return mesh_; }

  std::shared_ptr<VertexShader> vertex_shader() const { return vertex_shader_; }
  void set_vertex_shader(const std::shared_ptr<VertexShader> &vertex_shader) {
    vertex_shader_ = vertex_shader;
  }

  std::shared_ptr<FragmentShader> fragment_shader() const {
    return fragment_shader_;
  }
  void set_fragment_shader(
      const std::shared_ptr<FragmentShader> &fragment_shader) {
    fragment_shader_ = fragment_shader;
  }

  std::shared_ptr<Material> material() const { return material_; }
  void set_material(const std::shared_ptr<Material> &material) {
    material_ = material;
  }

 protected:
  math::vec3 scale_;

  std::shared_ptr<Mesh> mesh_ = nullptr;

  std::shared_ptr<VertexShader> vertex_shader_ = nullptr;
  std::shared_ptr<FragmentShader> fragment_shader_ = nullptr;

  std::shared_ptr<Material> material_ = nullptr;
};

class SpotLightObject : public SceneObject {
 public:
  void set_spot_light(const std::shared_ptr<SpotLight> &spot_light) {
    spot_light_ = spot_light;
  }

 protected:
  std::shared_ptr<SpotLight> spot_light_;
};

} // namespace scene

}  // namespace softrd

#endif  // SOFTRD_SCENE_OBJECT_H_