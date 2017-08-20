void generate_proof(unsigned long* h1_ptr, unsigned long* h2_ptr, unsigned long* h3_ptr, unsigned long* r1_ptr, unsigned long* r2_ptr, unsigned long* r3_ptr);

bool run_test(
	unsigned long* h1,
	unsigned long* h2,
	unsigned long* h3,
	unsigned long* r1,
	unsigned long* r2,
	unsigned long* r3,
	r1cs_ppzksnark_keypair<default_r1cs_ppzksnark_pp>& keypair,
	bool use_and_instead_of_xor,
	bool swap_r1_r2,
	bool goofy_verification_inputs
);
