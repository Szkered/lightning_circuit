#include <stdlib.h>
#include <iostream>
#include <boost/optional/optional_io.hpp>

#include "snark.hpp"
#include "zk_proof_generator.h"

using namespace libsnark;
using namespace std;

void generate_proof(unsigned long* h1_ptr, unsigned long* h2_ptr, unsigned long* h3_ptr, unsigned long* r1_ptr, unsigned long* r2_ptr, unsigned long* r3_ptr) {
	default_r1cs_ppzksnark_pp::init_public_params();
	auto keypair = generate_keypair<default_r1cs_ppzksnark_pp>();
	run_test(h1_ptr, h2_ptr, h3_ptr, r1_ptr, r2_ptr, r3_ptr, keypair, false, false, false);
}

bool run_test(
	unsigned long* h1,
	unsigned long* h2,
	unsigned long* h3,
	unsigned long* r1,
	unsigned long* r2,
	unsigned long* r3,
	r1cs_ppzksnark_keypair<default_r1cs_ppzksnark_pp>& keypair,
	// These are just for changing behavior
	// for testing purposes:
	bool use_and_instead_of_xor,
	bool swap_r1_r2,
	bool goofy_verification_inputs
) {
	// Initialize bit_vectors for all of the variables involved.
	std::vector<bool> h1_bv(256);
	std::vector<bool> h2_bv(256);
	std::vector<bool> h3_bv(256);
	std::vector<bool> r1_bv(256);
	std::vector<bool> r2_bv(256);
	std::vector<bool> r3_bv(256);

	{
		h1_bv = int_list_to_bits({ h1[0], h1[1], h1[2], h1[3], h1[4], h1[5], h1[6], h1[7], h1[8], h1[9],
			h1[10], h1[11], h1[12], h1[13], h1[14], h1[15], h1[16], h1[17], h1[18], h1[19],
			h1[20], h1[21], h1[22], h1[23], h1[24], h1[25], h1[26], h1[27], h1[28], h1[29],
			h1[30], h1[31] }, 8);
		h2_bv = int_list_to_bits({ h2[0], h2[1], h2[2], h2[3], h2[4], h2[5], h2[6], h2[7], h2[8], h2[9],
			h2[10], h2[11], h2[12], h2[13], h2[14], h2[15], h2[16], h2[17], h2[18], h2[19],
			h2[20], h2[21], h2[22], h2[23], h2[24], h2[25], h2[26], h2[27], h2[28], h2[29],
			h2[30], h2[31] }, 8);
		h3_bv = int_list_to_bits({ h3[0], h3[1], h3[2], h3[3], h3[4], h3[5], h3[6], h3[7], h3[8], h3[9],
			h3[10], h3[11], h3[12], h3[13], h3[14], h3[15], h3[16], h3[17], h3[18], h3[19],
			h3[20], h3[21], h3[22], h3[23], h3[24], h3[25], h3[26], h3[27], h3[28], h3[29],
			h3[30], h3[31] }, 8);
		r1_bv = int_list_to_bits({ r1[0], r1[1], r1[2], r1[3], r1[4], r1[5], r1[6], r1[7], r1[8], r1[9],
			r1[10], r1[11], r1[12], r1[13], r1[14], r1[15], r1[16], r1[17], r1[18], r1[19],
			r1[20], r1[21], r1[22], r1[23], r1[24], r1[25], r1[26], r1[27], r1[28], r1[29],
			r1[30], r1[31] }, 8);
		r2_bv = int_list_to_bits({ r2[0], r2[1], r2[2], r2[3], r2[4], r2[5], r2[6], r2[7], r2[8], r2[9],
			r2[10], r2[11], r2[12], r2[13], r2[14], r2[15], r2[16], r2[17], r2[18], r2[19],
			r2[20], r2[21], r2[22], r2[23], r2[24], r2[25], r2[26], r2[27], r2[28], r2[29],
			r2[30], r2[31] }, 8);
		r3_bv = int_list_to_bits({ r3[0], r3[1], r3[2], r3[3], r3[4], r3[5], r3[6], r3[7], r3[8], r3[9],
			r3[10], r3[11], r3[12], r3[13], r3[14], r3[15], r3[16], r3[17], r3[18], r3[19],
			r3[20], r3[21], r3[22], r3[23], r3[24], r3[25], r3[26], r3[27], r3[28], r3[29],
			r3[30], r3[31] }, 8);
	}
	if (swap_r1_r2) {
		// This swaps r1 and r2 which should test if the hashing
		// constraints work properly.
		auto tmp = r2_bv;
		r2_bv = r1_bv;
		r1_bv = tmp;
	}

	cout << "Trying to generate proof..." << endl;
	auto proof = generate_proof<default_r1cs_ppzksnark_pp>(keypair.pk, h1_bv, h2_bv, h3_bv, r1_bv, r2_bv, r3_bv);
	cout << "Proof generated!" << endl;
	cout << "Proof: " << proof << endl;

	if (!proof) {
		return false;
	}
	else {
		if (goofy_verification_inputs) {
			// [test] if we generated the proof but try to validate
			// with bogus inputs it shouldn't let us
			return verify_proof(keypair.vk, *proof, h2_bv, h1_bv, h3_bv);
		}
		else {
			// verification should not fail if the proof is generated!
			assert(verify_proof(keypair.vk, *proof, h1_bv, h2_bv, h3_bv));
			return true;
		}
	}
}