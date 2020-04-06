#include "renderer_api_addon.h"

#include <iostream>

softrd::vec3 ParseVec3(const Napi::Object& wrapped_vec3) {
  float x = wrapped_vec3.Get("x").ToNumber().FloatValue();
  float y = wrapped_vec3.Get("y").ToNumber().FloatValue();
  float z = wrapped_vec3.Get("z").ToNumber().FloatValue();
  return softrd::vec3(x, y, z);
}

Napi::FunctionReference RendererAPIAddon::constructor;

Napi::Object RendererAPIAddon::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env, "RendererAPIAddon",
                  {
                      InstanceMethod("plusOne", &RendererAPIAddon::PlusOne),
                      InstanceMethod("value", &RendererAPIAddon::GetValue),
                      InstanceMethod("multiply", &RendererAPIAddon::Multiply),
                      InstanceMethod("resetArrayBuffer",
                                     &RendererAPIAddon::ResetArrayBuffer),
                      InstanceMethod("drawFrame", &RendererAPIAddon::DrawFrame),
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

  int length = info.Length();

  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number value = info[0].As<Napi::Number>();
  this->value_ = value.DoubleValue();
  this->renderer_api_ = new softrd::RendererAPI();
  this->renderer_api_->InitExampleMesh();
}

Napi::Value RendererAPIAddon::GetValue(const Napi::CallbackInfo& info) {
  double num = this->value_;
  std::cout << "value = " << num << std::endl;

  return Napi::Number::New(info.Env(), num);
}

Napi::Value RendererAPIAddon::PlusOne(const Napi::CallbackInfo& info) {
  this->value_ = this->value_ + 1;

  return RendererAPIAddon::GetValue(info);
}

Napi::Value RendererAPIAddon::Multiply(const Napi::CallbackInfo& info) {
  Napi::Number multiple;
  if (info.Length() <= 0 || !info[0].IsNumber()) {
    multiple = Napi::Number::New(info.Env(), 1);
  } else {
    multiple = info[0].As<Napi::Number>();
  }

  Napi::Object obj = constructor.New(
      {Napi::Number::New(info.Env(), this->value_ * multiple.DoubleValue())});

  return obj;
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

  this->renderer_api_->ResetBuffer(array, length);
  return info.Env().Undefined();
}

Napi::Value RendererAPIAddon::DrawFrame(const Napi::CallbackInfo& info) {
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

  this->renderer_api_->DrawExampleMesh(array);

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

  std::cout << "addon draw scene" << std::endl;

  this->renderer_api_->DrawScene(array);

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

  auto keys = object_list.GetPropertyNames();

  for (int i = 0; i < keys.Length(); ++i) {
    auto key = keys.Get(i);
    Napi::Object wrapped_scene_object = object_list.Get(key).ToObject();

    const std::string& id =
        wrapped_scene_object.Get("id").ToString().Utf8Value();
    const softrd::vec3& position =
        ParseVec3(wrapped_scene_object.Get("position").ToObject());
    const softrd::vec3& rotation =
        ParseVec3(wrapped_scene_object.Get("rotation").ToObject());

    renderer_api_->SetSceneObject(id, position, rotation);
  }

  uint8_t* array = reinterpret_cast<uint8_t*>(buf.Data());
  size_t length = buf.ByteLength() / sizeof(uint8_t);
  memset(array, 0, buf.ByteLength());

  this->renderer_api_->DrawScene(array);

  return info.Env().Undefined();
}
