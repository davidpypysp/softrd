#include "src/interface/renderer_api.h"

namespace softrd {
RendererAPI::RendererAPI() {
  engine_ = std::make_unique<Engine>();
  engine_->Reset(640, 480);
}

void RendererAPI::DrawScene(uint8_t *buffer) {
  if (!buffer) {
    return;
  }

  engine_->DrawScene(buffer);
}

void RendererAPI::ResetBuffer(uint8_t *buffer, size_t size) {
  for (size_t index = 0; index < size; index += 4) {
    buffer[index] = 150;      // red
    buffer[index + 1] = 150;  // green
    buffer[index + 2] = 50;   // blue
    buffer[index + 3] = 255;  // alpha
  }
}

void RendererAPI::SetSceneObject(const std::string &id, const vec3 &position,
                                 const vec3 &rotation) {
  const auto &scene_manager = engine_->scene_manager();

  const auto &scene_object = scene_manager->GetSceneObject(id);
  if (scene_object) {
    scene_object->set_position(position);
    scene_object->set_rotation(rotation);
  } else {
    scene_manager->AddSceneObject(id, position, rotation);
  }
}

RendererAPI::~RendererAPI() {}

}  // namespace softrd
