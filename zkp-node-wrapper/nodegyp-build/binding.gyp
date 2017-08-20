{
  "targets": [
    {
      "target_name": "zklib",
      "sources": [ "zk_node_wrapper.cpp", "zk_proof_generator.h"],
	"libraries": [ "zk_proof_generator.a", "libsnark.so" ]
    }
  ]
}