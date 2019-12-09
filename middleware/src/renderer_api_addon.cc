#include "renderer_api_addon.h"

#include <iostream>

Napi::FunctionReference RendererAPIAddon::constructor;

Napi::Object RendererAPIAddon::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env, "RendererAPIAddon",
                  {InstanceMethod("plusOne", &RendererAPIAddon::PlusOne),
                   InstanceMethod("value", &RendererAPIAddon::GetValue),
                   InstanceMethod("multiply", &RendererAPIAddon::Multiply),
                   InstanceMethod("acceptArrayBuffer",
                                  &RendererAPIAddon::AcceptArrayBuffer)});

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
  this->renderer_api_->ExamplePrint();
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

Napi::Value RendererAPIAddon::AcceptArrayBuffer(
    const Napi::CallbackInfo& info) {
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

  // std::cout << "length = " << length << std::endl;

  // for (size_t index = 0; index < length; index += 4) {
  //   array[index] = 255;      // red
  //   array[index + 1] = 100;  // green
  //   array[index + 2] = 100;  // blue
  //   array[index + 3] = 255;  // alpha
  // }

  // // for (size_t index = 0; index < length; index++) {
  // //   fprintf(stderr, "array[%lu] is %d\n", index, array[index]);
  // }

  return info.Env().Undefined();
}
