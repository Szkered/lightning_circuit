#include <node.h>
#include "zk_proof_generator.h"
#define ZkIntHashSize 32

namespace zk_node_wrapper {

	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;
	using v8::Function;
	using v8::Uint32Array;
	using v8::Uint32;
	using v8::Integer;

	///<Summary>
	///Converts a V8 array to a standard unsigned long array
	///</Summary>
	unsigned long * convert_to_std_array(Local<Uint32Array> * v8_array) {
		unsigned long * std_array = new unsigned long[ZkIntHashSize];
		for (int i = 0; i < ZkIntHashSize; i++) {
			Integer * d = Integer::Cast((*(*v8_array)->Get(i)));
			unsigned long v = static_cast<unsigned long>(d->Value());
			std_array[i] = v;
		}
		return std_array;
	}

	void GetProof(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		Local<Uint32Array> l_h1 = Local<Uint32Array>::Cast(args[0]);
		Local<Uint32Array> l_h2 = Local<Uint32Array>::Cast(args[1]);
		Local<Uint32Array> l_h3 = Local<Uint32Array>::Cast(args[2]);
		Local<Uint32Array> l_r1 = Local<Uint32Array>::Cast(args[3]);
		Local<Uint32Array> l_r2 = Local<Uint32Array>::Cast(args[4]);
		Local<Uint32Array> l_r3 = Local<Uint32Array>::Cast(args[5]);
		unsigned long * h1 = convert_to_std_array(&l_h1);
		unsigned long * h2 = convert_to_std_array(&l_h2);
		unsigned long * h3 = convert_to_std_array(&l_h3);
		unsigned long * r1 = convert_to_std_array(&l_r1);
		unsigned long * r2 = convert_to_std_array(&l_r2);
		unsigned long * r3 = convert_to_std_array(&l_r3);
		generate_proof(h1, h2, h3, r1, r2, r3);
		args.GetReturnValue().Set(Integer::New(isolate, 0));
	}

	void init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "getProof", GetProof);
	}

	NODE_MODULE(zklib, init)

} 