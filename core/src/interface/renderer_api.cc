#include "src/interface/renderer_api.h"

namespace softrd {
RendererAPI::RendererAPI() { this->Reset(640, 480); }

void RendererAPI::ResetBuffer(uint8_t *buffer, size_t size) {
  for (size_t index = 0; index < size; index += 4) {
    buffer[index] = 150;      // red
    buffer[index + 1] = 150;  // green
    buffer[index + 2] = 50;   // blue
    buffer[index + 3] = 255;  // alpha
  }
}

void RendererAPI::SetSceneObject(const std::string &id,
                                 const math::vec3 &position,
                                 const math::vec3 &rotation) {
  const auto &scene_object = scene_manager_->GetSceneObject(id);
  if (scene_object) {
    scene_object->set_position(position);
    scene_object->set_rotation(rotation);
  } else {
    scene_manager_->AddSceneObject(id, position, rotation);
  }
}

}  // namespace softrd
