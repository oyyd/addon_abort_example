#include <napi.h>

class MyObject : public Napi::ObjectWrap<MyObject> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  MyObject(const Napi::CallbackInfo& info);
  ~MyObject();
};

Napi::Object MyObject::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env,
                  "MyObject",
                  {});

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("MyObject", func);
  return exports;
}

MyObject::MyObject(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<MyObject>(info) {
  this->Ref();
}

MyObject::~MyObject() {
  uint32_t count = -1;
  count = this->Unref();
  fprintf(stderr, "count %d\n", count);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return MyObject::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)
