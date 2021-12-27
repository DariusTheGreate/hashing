#include "mybits.h"
#include "types.h"
#include "mymacros.h"

#include "Sha.h"

#include <cstring>

const uint32 SHA::K[64] = 
{0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void SHA::init(){
	H[0] = 0x6a09e667;
	H[1] = 0xbb67ae85;
	H[2] = 0x3c6ef372;
	H[3] = 0xa54ff53a;
	H[4] = 0x510e527f;
	H[5] = 0x9b05688c;
	H[6] = 0x1f83d9ab;
	H[7] = 0x5be0cd19;

	len = 0;
	memset(result,0, RESULT_SIZE);
}

void SHA::update(const uint8* message, uint32 len_in){
	std::cout << "\n\n";
	uint32 block_number;
	uint32 new_len, rem_len, tmp_len;
	tmp_len = SHA_BLOCK_SIZE - len;
	rem_len = len_in < tmp_len ? len_in : tmp_len;
	memcpy(&block[len], message, rem_len);

	for (size_t i = len; i < len_in; ++i) {
		std::bitset<8> symbol(block[i]);
		//std::cout << symbol;
	}
	//std::cout << "\n\n";

	if(len + len_in < SHA_BLOCK_SIZE){
		len+=len_in;
		return;
	}

	else{
		std::cout << "not allowed\n\n";
	}
}

void SHA::final(){
	unsigned int block_nb;//block_number
	unsigned int pm_len;//lefted message
	unsigned int len_b;//len in binary
	int i;
	block_nb = (1 + ((SHA_BLOCK_SIZE - 9) < (len % SHA_BLOCK_SIZE)));
	len_b = (0 + len) << 3;
	pm_len = block_nb << 6;
	memset(block + len, 0, pm_len - len);//zero out shit
	block[len] = 0x80;//separate 1
	
	sha_unpack32(len_b, block + pm_len - 4);//set len at the end

	transform(block, block_nb);
	

	for (i = 0 ; i < 8; i++) {
		sha_unpack32(H[i], &result[i << 2]);
	}
}

void SHA::transform(const unsigned char *message, unsigned int block_nb)
{
	init();
	uint32 w[64];//includes garbage
	uint32 wv[8];
	uint32 t1, t2;
	const unsigned char *sub_block;//processing block
	int i;
	int j;
	for (i = 0; i < (int) block_nb; i++) {
		sub_block = message + (i << 6);//iterate pointer by 64bits
		//iterate over block by 4 bit (x16)
		for (j = 0; j < 16; j++) {
			sha_pack32(&sub_block[j << 2], &w[j]);
		}

		for (size_t wn = 0; wn < 64; ++wn) {
			std::bitset<32> symbol(w[wn]);
			//std::cout << symbol << "\n";
		}
		
		//process garbage
		for (j = 16; j < 64; j++) {
			w[j] =  sha_f4(w[j -  2]) + w[j -  7] + sha_f3(w[j - 15]) + w[j - 16];
		}

		//here message schedule aka garbage is prepatred
			
		for (j = 0; j < 8; j++) {
			wv[j] = H[j];
		} 

		for (j = 0; j < 64; j++) {
			t1 = wv[7] + sha_f2(wv[4]) + sha_ch(wv[4], wv[5], wv[6]) + K[j] + w[j];
			t2 = sha_f1(wv[0]) + sha_maj(wv[0], wv[1], wv[2]);
			
			wv[7] = wv[6];
			wv[6] = wv[5];
			wv[5] = wv[4];
			wv[4] = wv[3] + t1;
			wv[3] = wv[2];
			wv[2] = wv[1];
			wv[1] = wv[0];
			wv[0] = t1 + t2;
		}

		for (j = 0; j < 8; j++) {
			H[j] += wv[j];
		}
	}
}

std::string SHA::print_result(){
	char buf[2*SHA::RESULT_SIZE+1];
	buf[2*SHA::RESULT_SIZE] = 0;
	for (int i = 0; i < SHA::RESULT_SIZE; i++)
		sprintf(buf+i*2, "%02x", result[i]);
	std::cout << "\n\n" <<  std::string(buf);
	return std::string(buf);
}
