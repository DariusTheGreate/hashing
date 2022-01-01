#ifndef _MY_BITS_
#define _MY_BITS_

#include <bitset>

#include "types.h"
#include "mymacros.h"

inline uint32 rotr(uint32 x, uint8 n){
	return ((x >> n) | (x << ((sizeof(x) << 3) - n)));
}

inline uint32 rotl(uint32 x, uint8 n){
	return ((x << n) | (x >> ((sizeof(x) << 3) - n)));
}

inline uint32 sha_ch(uint32 x, uint32 y, uint32 z){
	return ((x & y) ^ (~x & z));
}

inline uint32 sha_maj(uint32 x, uint32 y, uint32 z){
	return ((x & y) ^ (x & z) ^ (y & z));
}

inline uint32 sha_shfr(uint32 val, uint8 n){
	return (val >> n);
}

inline uint32 sha_f1(uint32 x){
	return (rotr(x,  2) ^ rotr(x, 13) ^ rotr(x, 22));
}

inline uint32 sha_f2(uint32 x){
	return (rotr(x,  6) ^ rotr(x, 11) ^ rotr(x, 25));
}

inline uint32 sha_f3(uint32 x){
	return (rotr(x, 7) ^ rotr(x, 18) ^ sha_shfr(x, 3));
}

inline uint32 sha_f4(uint32 x){
	return (rotr(x, 17) ^ rotr(x, 19) ^ sha_shfr(x, 10));
}

inline void sha_pack32(const uint8* str, uint32* x){
	*(x) = ((uint32) *((str) + 3)) | ((uint32) *((str) + 2) << 8) | ((uint32) *((str) + 1) << 16) | ((uint32) *((str)) << 24);
}

inline void sha_unpack32(uint32 x, uint8* str){
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

//MD5

inline uint32 F(uint32 x, uint32 y, uint32 z) {return (x & y) | (~x & z);};
inline uint32 G(uint32 x, uint32 y, uint32 z) {return (x & z) | (y & ~z);};
inline uint32 H(uint32 x, uint32 y, uint32 z) {return x ^ y ^ z;};
inline uint32 I(uint32 x, uint32 y, uint32 z) {return y ^ (x | ~z);};


inline void FF(uint32 &a, uint32 b, uint32 c, uint32 d, uint32 Xk, uint32 s, uint32 i) {
	a += F(b,c,d) + Xk + i;
	a = rotl(a, s);
	a += b;
};

inline void GG(uint32 &a, uint32 b, uint32 c, uint32 d, uint32 Xk, uint32 s, uint32 i) {
	a += G(b,c,d) + Xk + i;
	a = rotl(a, s);
	a += b;
};

inline void HH(uint32 &a, uint32 b, uint32 c, uint32 d, uint32 Xk, uint32 s, uint32 i) {
	a += H(b,c,d) + Xk + i;
	a = rotl(a, s);
	a += b;        
};

inline void II(uint32 &a, uint32 b, uint32 c, uint32 d, uint32 Xk, uint32 s, uint32 i) {
	a += I(b,c,d) + Xk + i;
	a = rotl(a, s);
	a += b;
};


#endif
