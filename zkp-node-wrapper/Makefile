OPTFLAGS = -march=native -mtune=native -O2
CXXFLAGS += -g -Wall -Wextra -Wno-unused-parameter -std=c++11 -fPIC -Wno-unused-variable -I depinst/include -I depinst/include/libsnark -DUSE_ASM -DCURVE_ALT_BN128
LDFLAGS += -flto

DEPSRC=depsrc
DEPINST=depinst

LDLIBS += -L depinst/lib -Wl,-rpath depinst/lib -L . -lsnark -lgmpxx -lgmp -lboost_system

all:
	$(CXX) -o zk_proof_generator.o src/zk_proof_generator.cpp -c $(CXXFLAGS)
	ar rcs zk_proof_generator.a zk_proof_generator.o depinst/lib/libsnark.so
clean:
	$(RM) zk_proof_generator.o zk_proof_generator.a