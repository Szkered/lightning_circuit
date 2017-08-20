#include <stdlib.h>
#include <iostream>
#include <node.h>
#include <boost/optional/optional_io.hpp>

#include "snark.hpp"

using namespace libsnark;
using namespace std;

namespace nodeLibsnark {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "mocked out proof"));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "generate_proof", Method);
}

NODE_MODULE(addon, init)

}  // namespace demo
