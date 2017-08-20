{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "src/node.cpp" ],
      "include_dirs": [
        "depinst/include/", "depinst/include/libsnark/ -DUSE_ASM -DCURVE_ALT_BN128"
      ]
    }
  ]}
