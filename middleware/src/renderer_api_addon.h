#ifndef SOFTRD_RENDERER_API_ADDON_H_
#define SOFTRD_RENDERER_API_ADDON_H_

#include <napi.h>

class RendererAPIAddon : public Napi::ObjectWrap<RendererAPIAddon> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  RendererAPIAddon(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;

  Napi::Value GetValue(const Napi::CallbackInfo& info);
  Napi::Value PlusOne(const Napi::CallbackInfo& info);
  Napi::Value Multiply(const Napi::CallbackInfo& info);

  double value_;
};

#endif  // SOFTRD_RENDERER_API_ADDON_H_
