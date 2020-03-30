#ifndef SOFTRD_SCENE_OBJECT_H_
#define SOFTRD_SCENE_OBJECT_H_

#include <memory>

#include "src/components/mesh.h"
#include "src/modules/fragment_shader.h"
#include "src/modules/vertex_shader.h"

namespace softrd {

class SceneObject {
 public:
  void set_id(const std::string &id) { id_ = id; }
  std::string id() const { return id_; }

  void set_position(const vec3 &position) { position_ = position; }
  vec3 position() const { return position_; }

  void set_rotation(const vec3 &rotation) { rotation_ = rotation; }
  vec3 rotation() const { return rotation_; }

  void set_scale(const vec3 &scale) { scale_ = scale; }
  vec3 scale() const { return scale_; }

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

  void set_material(const std::shared_ptr<Material> &material) {
    material_ = material;
  }

 private:
  std::string id_;

  vec3 position_;
  vec3 rotation_;
  vec3 scale_;

  std::shared_ptr<Mesh> mesh_ = nullptr;

  std::shared_ptr<VertexShader> vertex_shader_ = nullptr;
  std::shared_ptr<FragmentShader> fragment_shader_ = nullptr;

  std::shared_ptr<Material> material_ = nullptr;
};

}  // namespace softrd

#endif  // SOFTRD_SCENE_OBJECT_H_