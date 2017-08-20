# NodeJS wrapper for libsnark

## Direct use of zklib.node without makefile

Tested environment: Ubuntu 16.04

1. Add zklib.node to 
``` 
node_modules
```
2. Add libsnark.so dependency to 
```
/usr/lib
```

3. Install libsnark dependencies:
```
sudo apt-get install build-essential git libgmp3-dev libprocps4-dev libgtest-dev python-markdown libboost-all-dev libssl-dev
```
4. Reference module in node.js script. 
```
const zklib = require('zklib');
zklib.getProof(h1, h2, h3, r1, r2, r3);
```
Example is found at 
```
/nodejs/example.js
```

## Generating node module from scratch

### Creating libsnark with callable interface as static library file

1. Clone /zkp folder in repo.
2. Set up /zkp dependencies + libsnark library following instructions in /zkp.
3. Add to /zkp/src
```
zk_proof_generator.cpp, zk_proof_generator.h 
```
4. Replace /zkp/Makefile with Makefile here
5. Run makefile to create 
```
zk_proof_generator.a
```

### Node-gyp compile zklib module

1. Install node-gyp using:
```
npm install -g node-gyp
```
2. Go to nodegyp-build folder
```
cd nodegyp-build
```
3. Call node-gyp configure
4. Place dependencies inside created build folder
```
zk_proof_generator.a, libsnark.so
```
5. node-gyp build
6. node module can be found in:
```
/build/release/zklib.node
```