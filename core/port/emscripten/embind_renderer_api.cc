#include <emscripten/bind.h>

#include "src/interface/renderer_api.h"

using namespace emscripten;

softrd::math::vec3 ParseVec3(const val& vec3_object) {
  return softrd::math::vec3(vec3_object["x"].as<float>(),
                            vec3_object["y"].as<float>(),
                            vec3_object["z"].as<float>());
}

class EmbindRendererAPI : public softrd::RendererAPI {
 public:
  val GetFrameBufferView() {
    std::vector<uint8_t>* frame_buffer_ptr =
        rendering_pipeline_->GetFrameBufferPtr();
    auto& frame_buffer = *frame_buffer_ptr;
    return val(typed_memory_view(frame_buffer.size(), &frame_buffer[0]));
  }

  // object_list: {
  //  key: {
  //   id: string;
  //   position: math::vec3;
  //   rotation: math::vec3
  //  }
  // }
  inline void DrawSceneFromObjectList(const emscripten::val& object_list) {
    // val::global("console").call<val>("log", object_list);

    val keys = val::global("Object").call<val>("keys", object_list);
    const int length = keys["length"].as<int>();
    for (int i = 0; i < length; ++i) {
      const auto& key = keys[i].as<std::string>();
      const auto& scene_object = object_list[key];

      const auto& id = scene_object["id"].as<std::string>();
      const auto& position = ParseVec3(scene_object["position"]);
      const auto& rotation = ParseVec3(scene_object["rotation"]);
      this->SetSceneObject(id, position, rotation);
    }

    this->DrawSceneObjects();
  }

  // move_obj: math::vec3
  inline void MoveCamera(const emscripten::val& move_obj) {
    const auto& move = ParseVec3(move_obj);
    this->MoveSceneCamera(move);
  }

  // rotation_obj: math::vec3
  inline void RotateCamera(const emscripten::val& rotation_obj) {
    const auto& rotation = ParseVec3(rotation_obj);
    this->RotateSceneCamera(rotation);
  }
};

EMSCRIPTEN_BINDINGS(embind_renderer_api) {
  class_<EmbindRendererAPI>("RendererAPI")
      .constructor<>()
      .function("setSceneObject", &EmbindRendererAPI::SetSceneObject)
      .function("drawSceneFromObjectList",
                &EmbindRendererAPI::DrawSceneFromObjectList)
      .function("getFrameBufferView", &EmbindRendererAPI::GetFrameBufferView)
      .function("moveCamera", &EmbindRendererAPI::MoveCamera)
      .function("rotateCamera", &EmbindRendererAPI::RotateCamera);
}
