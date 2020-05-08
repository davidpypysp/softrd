#include "renderer_api_addon.h"

#include <iostream>

softrd::math::vec3 ParseVec3(const Napi::Object& wrapped_vec3) {
  float x = wrapped_vec3.Get("x").ToNumber().FloatValue();
  float y = wrapped_vec3.Get("y").ToNumber().FloatValue();
  float z = wrapped_vec3.Get("z").ToNumber().FloatValue();
  return softrd::math::vec3(x, y, z);
}

Napi::FunctionReference RendererAPIAddon::constructor;

Napi::Object RendererAPIAddon::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env, "RendererAPIAddon",
                  {
                      InstanceMethod("resetArrayBuffer",
                                     &RendererAPIAddon::ResetArrayBuffer),
                      InstanceMethod("drawScene", &RendererAPIAddon::DrawScene),
                      InstanceMethod("drawSceneObjects",
                                     &RendererAPIAddon::DrawSceneObjects),
                  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("RendererAPIAddon", func);
  return exports;
}

RendererAPIAddon::RendererAPIAddon(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<RendererAPIAddon>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  renderer_api_ = std::make_unique<softrd::RendererAPI>();
}

Napi::Value RendererAPIAddon::ResetArrayBuffer(const Napi::CallbackInfo& info) {
  if (info.Length() != 1) {
    Napi::Error::New(info.Env(), "Expected exactly one argument")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsArrayBuffer()) {
    Napi::Error::New(info.Env(), "Expected an ArrayBuffer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  Napi::ArrayBuffer buf = info[0].As<Napi::ArrayBuffer>();

  uint8_t* array = reinterpret_cast<uint8_t*>(buf.Data());
  size_t length = buf.ByteLength() / sizeof(uint8_t);

  renderer_api_->ResetBuffer(array, length);

  return info.Env().Undefined();
}

Napi::Value RendererAPIAddon::DrawScene(const Napi::CallbackInfo& info) {
  if (info.Length() != 1) {
    Napi::Error::New(info.Env(), "Expected exactly one argument")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsArrayBuffer()) {
    Napi::Error::New(info.Env(), "Expected an ArrayBuffer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  Napi::ArrayBuffer buf = info[0].As<Napi::ArrayBuffer>();

  uint8_t* array = reinterpret_cast<uint8_t*>(buf.Data());
  size_t length = buf.ByteLength() / sizeof(uint8_t);
  memset(array, 0, length);

  renderer_api_->DrawScene(array);
  return info.Env().Undefined();
}

Napi::Value RendererAPIAddon::DrawSceneObjects(const Napi::CallbackInfo& info) {
  if (info.Length() != 2) {
    Napi::Error::New(info.Env(), "Expected exactly one argument")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsArrayBuffer()) {
    Napi::Error::New(info.Env(), "Expected an ArrayBuffer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[1].IsObject()) {
    Napi::Error::New(info.Env(), "Expected an Object")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  Napi::ArrayBuffer buf = info[0].As<Napi::ArrayBuffer>();
  Napi::Object object_list = info[1].As<Napi::Object>();

  const auto& keys = object_list.GetPropertyNames();

  for (size_t i = 0; i < keys.Length(); ++i) {
    const auto& key = keys.Get(i);
    const Napi::Object& wrapped_scene_object = object_list.Get(key).ToObject();

    const std::string& id =
        wrapped_scene_object.Get("id").ToString().Utf8Value();
    const softrd::math::vec3& position =
        ParseVec3(wrapped_scene_object.Get("position").ToObject());
    const softrd::math::vec3& rotation =
        ParseVec3(wrapped_scene_object.Get("rotation").ToObject());

    renderer_api_->SetSceneObject(id, position, rotation);
  }

  uint8_t* array = reinterpret_cast<uint8_t*>(buf.Data());
  memset(array, 0, buf.ByteLength());
  renderer_api_->DrawScene(array);

  return info.Env().Undefined();
}
