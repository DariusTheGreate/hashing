#ifndef _MY_BITS_
#define _MY_BITS_

#include <bitset>

#include "types.h"
#include "mymacros.h"

inline uint32 sha_ch(uint32 x, uint32 y, uint32 z){
	return ((x & y) ^ (~x & z));
}

inline uint32 sha_maj(uint32 x, uint32 y, uint32 z){
	return ((x & y) ^ (x & z) ^ (y & z));
}

inline uint32 sha_shfr(uint32 val, uint8 n){
	return (val >> n);
}

inline uint32 sha_rotr(uint32 x, uint8 n){
	return ((x >> n) | (x << ((sizeof(x) << 3) - n)));
}

inline uint32 sha_rotl(uint32 x, uint8 n){
	return ((x << n) | (x >> ((sizeof(x) << 3) - n)));
}

inline uint32 sha_f1(uint32 x){
	return (sha_rotr(x,  2) ^ sha_rotr(x, 13) ^ sha_rotr(x, 22));
}

inline uint32 sha_f2(uint32 x){
	return (sha_rotr(x,  6) ^ sha_rotr(x, 11) ^ sha_rotr(x, 25));
}

inline uint32 sha_f3(uint32 x){
	return (sha_rotr(x, 7) ^ sha_rotr(x, 18) ^ sha_shfr(x, 3));
}

inline uint32 sha_f4(uint32 x){
	return (sha_rotr(x, 17) ^ sha_rotr(x, 19) ^ sha_shfr(x, 10));
}

inline void sha_pack32(const unsigned char* str, uint32* x){
	*(x) = ((uint32) *((str) + 3)) | ((uint32) *((str) + 2) << 8) | ((uint32) *((str) + 1) << 16) | ((uint32) *((str)) << 24);
}

inline void sha_unpack32(uint32 x, unsigned char* str){
	*((str) + 3) = (uint8) ((x));
    *((str) + 2) = (uint8) ((x) >>  8);
    *((str) + 1) = (uint8) ((x) >> 16);
    *((str) + 0) = (uint8) ((x) >> 24);
}

inline void print_data_binary(uint8 block[], size_t pm_len){
	for (size_t i = 0; i < pm_len; ++i) {
		std::bitset<8> symbol(block[i]);
		print(symbol)
	}
}

#endif
