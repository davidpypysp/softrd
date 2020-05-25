#include <emscripten/bind.h>

#include "src/interface/renderer_api.h"

using namespace emscripten;

class EmbindRendererAPI : public softrd::RendererAPI {
 public:
  val GetFrameBufferView() {
    std::vector<uint8_t>* frame_buffer_ptr =
        rendering_pipeline_->GetFrameBufferPtr();
    auto& frame_buffer = *frame_buffer_ptr;
    return val(typed_memory_view(frame_buffer.size(), &frame_buffer[0]));
  }

  inline void DrawSceneObjectsBase() { this->DrawSceneObjects(); }
};

EMSCRIPTEN_BINDINGS(embind_renderer_api) {
  class_<EmbindRendererAPI>("RendererAPI")
      .constructor<>()
      .function("setSceneObject", &EmbindRendererAPI::SetSceneObject)
      .function("drawSceneObjects", &EmbindRendererAPI::DrawSceneObjectsBase)
      .function("getFrameBufferView", &EmbindRendererAPI::GetFrameBufferView);
}
