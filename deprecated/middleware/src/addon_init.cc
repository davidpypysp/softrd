#include <napi.h>
#include "renderer_api_addon.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return RendererAPIAddon::Init(env, exports);
}

NODE_API_MODULE(addon_init, InitAll)
