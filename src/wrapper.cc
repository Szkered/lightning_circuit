#include <stdlib.h>
#include <iostream>
#include <boost/optional/optional_io.hpp>

#include "snark.hpp"
// #include "test.h"
#include <node.h>

using namespace libsnark;
using namespace std;

namespace wrapper {

  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::FunctionTemplate;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void generateProof(const FunctionCallbackInfo<Value>& args) {
    // Initialize the curve parameters.
    default_r1cs_ppzksnark_pp::init_public_params();
    // Generate the verifying/proving keys. (This is trusted setup!)
    auto keypair = generate_keypair<default_r1cs_ppzksnark_pp>();

    // Testing bit_vectors
    std::vector<bool> h1_bv(256);
    std::vector<bool> h2_bv(256);
    std::vector<bool> h3_bv(256);
    std::vector<bool> r1_bv(256);
    std::vector<bool> r2_bv(256);
    std::vector<bool> r3_bv(256);
    
    {
      // r3 = r1 + r2
      // r3 = 30; r1 = 10; r2 = 20
      h1_bv = int_list_to_bits({129, 176, 74, 228, 148, 78, 23, 4, 166, 91, 195, 165, 123, 111, 195, 176, 106, 107, 146, 62, 60, 85, 141, 97, 31, 106, 133, 75, 85, 57, 236, 19}, 8);
      h2_bv = int_list_to_bits({77, 104, 191, 146, 29, 127, 207, 159, 153, 162, 126, 40, 245, 155, 135, 92, 35, 65, 147, 249, 195, 48, 64, 61, 207, 41, 241, 135, 43, 229, 124, 205}, 8);
      h3_bv = int_list_to_bits({78, 153, 116, 122, 61, 65, 254, 131, 24, 196, 65, 155, 123, 104, 135, 65, 216, 239, 112, 150, 54, 129, 41, 225, 72, 148, 221, 189, 172, 49, 121, 94}, 8);
      r1_bv = int_list_to_bits({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10}, 8);
      r2_bv = int_list_to_bits({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20}, 8);
      r3_bv = int_list_to_bits({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30}, 8);
    }

    auto proof = generate_proof<default_r1cs_ppzksnark_pp>(keypair.pk, h1_bv, h2_bv, h3_bv, r1_bv, r2_bv, r3_bv);

    Local<Object> obj = Object::New(isolate);
    obj->Set()
    return proof
  }
  
} // namespace wrapper
