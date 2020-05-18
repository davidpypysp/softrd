#include <emscripten/bind.h>

#include "src/interface/renderer_api.h"

using namespace emscripten;
uint8_t* byteBuffer = (uint8_t*)malloc(8);
size_t bufferLength = 8;

val getBytes() {
  byteBuffer[0] = 0;
  byteBuffer[1] = 1;
  byteBuffer[2] = 2;
  byteBuffer[3] = 2;
  byteBuffer[4] = 2;
  return val(typed_memory_view(bufferLength, byteBuffer));
}

class EmbindRendererAPI : public softrd::RendererAPI {
 public:
  val GetBytes() { return val(typed_memory_view(bufferLength, byteBuffer)); }
};

EMSCRIPTEN_BINDINGS(embind_renderer_api) {
  class_<EmbindRendererAPI>("RendererAPI")
      .constructor<>()
      .function("resetBuffer", &EmbindRendererAPI::ResetBuffer,
                allow_raw_pointers())
      .function("drawScene", &EmbindRendererAPI::DrawScene,
                allow_raw_pointers())
      .function("getBytes", &EmbindRendererAPI::GetBytes)
      .function("setSceneObject", &EmbindRendererAPI::SetSceneObject);
  function("getBytes", &getBytes);
}
