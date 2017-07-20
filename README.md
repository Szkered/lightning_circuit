
This is a SNARK implementation using libsnark for the following:

``ZkPoK{ (R1, R2, R3): Hi = sha256(Ri) and R3 = R1 + R2 }``

Read: given `H1`, `H2`, `H3`, prove you know `R1`, `R2`, `R3` such that `R1` is the preimage of `H1`, `R2` is the preimage of `H2`, `R3` is the preimage of `H3`, and `R3` is `R1 + R2`.

This is an implementation and benchmark of the "Receive" zk-SNARK in the Confidential Transaction scheme from this article: <https://media.consensys.net/introduction-to-zksnarks-with-examples-3283b554fc3b>.

Code based on <https://github.com/ebfull/lightning_circuit>.

## performance

on my computer (MacBook Pro Early 2015):

* **key generation time**: 22.1s
* **proof generation time**: 5.14s
* **verification time**: 0.1445ss
* **proof size**: 2294 bits
* **proving key size**: 153200114 bits
* **verifying key size**: 4586 bits
* **R1CS constraints**: 83766 (mostly sha256-related)

## howto

``./get-libsnark && make && ./test``

## anatomy

* `src/gadget.hpp` exposes the gadget, which is an abstraction of related constraint
and witness behavior in a circuit. This gadget uses other gadgets, creates its own
constraints, and exposes an interface for building input maps.

* `src/snark.hpp` exposes a loose wrapper around the constraint system and
key generation used by `test.cpp` to construct proofs and verify them as necessary.
