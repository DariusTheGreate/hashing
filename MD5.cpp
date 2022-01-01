#include "mybits.h"
#include "types.h"
#include "mymacros.h"

#include "MD5.h"
#include <cstring>

const uint32 S1[4] = {7, 12, 17, 22};
const uint32 S2[4] = {5, 9,  14, 20};
const uint32 S3[4] = {4, 11, 16, 23};
const uint32 S4[4] = {6, 10, 15, 21};

const uint32 MD5::T[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
						0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
						0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
						0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
						0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
						0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
						0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
						0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

void MD5::init(){
    A = 0x67452301;
    B = 0xefcdab89;
    C = 0x98badcfe;
    D = 0x10325476;
	len = 0;
	memset(result,0, RESULT_SIZE);
}

void MD5::update(const uint8* message, uint32 len_in){
	std::cout << "\n\n";
	uint32 block_number;
	uint32 new_len, rem_len, tmp_len;
	tmp_len = MD5::MD5_BLOCK_SIZE - len;
	rem_len = len_in < tmp_len ? len_in : tmp_len;
	memcpy(&block[len], message, rem_len);

	std::cout << "message in binary:\n";
	for (size_t i = len; i < len_in; ++i) {
		std::bitset<8> symbol(block[i]);
		std::cout << symbol;
	}
	std::cout << "\n\n";

	if(len + len_in < MD5_BLOCK_SIZE){
		len+=len_in;
		return;
	}

	else{
		std::cout << "not allowed\n\n";
	}
}

void MD5::final(){
	uint32 block_nb;//block_number
	uint32 pm_len;//lefted message
	uint32 len_b;//len in binary
	int i;
	block_nb = (1 + ((MD5_BLOCK_SIZE - 9) < (len % MD5_BLOCK_SIZE)));
	len_b = (0 + len) << 3;
	pm_len = block_nb << 6;
	memset(block + len, 0, pm_len - len);//zero out shit
	block[len] = 0x80;//separate 1

	sha_unpack32(len_b, block + pm_len - 4);//set len at the end

	print("message we construct:\n");
	for (size_t i = 0; i < MD5_BLOCK_SIZE; ++i) {
		std::bitset<8> symbol(block[i]);
		std::cout << symbol;
	}
	print("\n\n");
		
	transform(block, block_nb);
}

void MD5::transform(const uint8 *message, uint32 block_nb)
{
	for (int i = 0; i < (int) block_nb; i++) {
		print("message we get if we separate it:\n");
		for (int j = 0; j < MD5_BLOCK_SIZE; j+=4) {
			print_data_binary((uint8 *)&message[j], 4);
			std::cout << "\n";
		}
		print("\n\n");

		uint32 X[16];
        for (uint32 i = 0; i < 16; i++) {
            memcpy(X + i, message + 4 * i, 4);
        }
        
        print("X is:\n");
        for(size_t i = 0; i < 16; ++i){
        	print_data_binary((uint8*)&X[i], 4);
        	print("\n");
        }
        print("\n\n");

        uint32 AA = A, BB = B, CC = C, DD = D;

        FF(A, B, C, D, X[0 ], S1[0], MD5::T[0]);
        FF(D, A, B, C, X[1 ], S1[1], MD5::T[1] );
        FF(C, D, A, B, X[2 ], S1[2], MD5::T[2] );
        FF(B, C, D, A, X[3 ], S1[3], MD5::T[3] );
        FF(A, B, C, D, X[4 ], S1[0], MD5::T[4] );
        FF(D, A, B, C, X[5 ], S1[1], MD5::T[5] );
        FF(C, D, A, B, X[6 ], S1[2], MD5::T[6] );
        FF(B, C, D, A, X[7 ], S1[3], MD5::T[7] );
        FF(A, B, C, D, X[8 ], S1[0], MD5::T[8] );
        FF(D, A, B, C, X[9 ], S1[1], MD5::T[9] );
        FF(C, D, A, B, X[10], S1[2], MD5::T[10]);
        FF(B, C, D, A, X[11], S1[3], MD5::T[11]);
        FF(A, B, C, D, X[12], S1[0], MD5::T[12]);
        FF(D, A, B, C, X[13], S1[1], MD5::T[13]);
        FF(C, D, A, B, X[14], S1[2], MD5::T[14]);
        FF(B, C, D, A, X[15], S1[3], MD5::T[15]);

        GG(A, B, C, D, X[1 ], S2[0], MD5::T[16]);
        GG(D, A, B, C, X[6 ], S2[1], MD5::T[17]);
        GG(C, D, A, B, X[11], S2[2], MD5::T[18]);
        GG(B, C, D, A, X[0 ], S2[3], MD5::T[19]);
        GG(A, B, C, D, X[5 ], S2[0], MD5::T[20]);
        GG(D, A, B, C, X[10], S2[1], MD5::T[21]);
        GG(C, D, A, B, X[15], S2[2], MD5::T[22]);
        GG(B, C, D, A, X[4 ], S2[3], MD5::T[23]);
        GG(A, B, C, D, X[9 ], S2[0], MD5::T[24]);
        GG(D, A, B, C, X[14], S2[1], MD5::T[25]);
        GG(C, D, A, B, X[3 ], S2[2], MD5::T[26]);
        GG(B, C, D, A, X[8 ], S2[3], MD5::T[27]);
        GG(A, B, C, D, X[13], S2[0], MD5::T[28]);
        GG(D, A, B, C, X[2 ], S2[1], MD5::T[29]);
        GG(C, D, A, B, X[7 ], S2[2], MD5::T[30]);
        GG(B, C, D, A, X[12], S2[3], MD5::T[31]);

        HH(A, B, C, D, X[5 ], S3[0], MD5::T[32]);
        HH(D, A, B, C, X[8 ], S3[1], MD5::T[33]);
        HH(C, D, A, B, X[11], S3[2], MD5::T[34]);
        HH(B, C, D, A, X[14], S3[3], MD5::T[35]);
        HH(A, B, C, D, X[1 ], S3[0], MD5::T[36]);
        HH(D, A, B, C, X[4 ], S3[1], MD5::T[37]);
        HH(C, D, A, B, X[7 ], S3[2], MD5::T[38]);
        HH(B, C, D, A, X[10], S3[3], MD5::T[39]);
        HH(A, B, C, D, X[13], S3[0], MD5::T[40]);
        HH(D, A, B, C, X[0 ], S3[1], MD5::T[41]);
        HH(C, D, A, B, X[3 ], S3[2], MD5::T[42]);
        HH(B, C, D, A, X[6 ], S3[3], MD5::T[43]);
        HH(A, B, C, D, X[9 ], S3[0], MD5::T[44]);
        HH(D, A, B, C, X[12], S3[1], MD5::T[45]);
        HH(C, D, A, B, X[15], S3[2], MD5::T[46]);
        HH(B, C, D, A, X[2 ], S3[3], MD5::T[47]);

        II(A, B, C, D, X[0 ], S4[0], MD5::T[48]);
        II(D, A, B, C, X[7 ], S4[1], MD5::T[49]);
        II(C, D, A, B, X[14], S4[2], MD5::T[50]);
        II(B, C, D, A, X[5 ], S4[3], MD5::T[51]);
        II(A, B, C, D, X[12], S4[0], MD5::T[52]);
        II(D, A, B, C, X[3 ], S4[1], MD5::T[53]);
        II(C, D, A, B, X[10], S4[2], MD5::T[54]);
        II(B, C, D, A, X[1 ], S4[3], MD5::T[55]);
        II(A, B, C, D, X[8 ], S4[0], MD5::T[56]);
        II(D, A, B, C, X[15], S4[1], MD5::T[57]);
        II(C, D, A, B, X[6 ], S4[2], MD5::T[58]);
        II(B, C, D, A, X[13], S4[3], MD5::T[59]);
        II(A, B, C, D, X[4 ], S4[0], MD5::T[60]);
        II(D, A, B, C, X[11], S4[1], MD5::T[61]);
        II(C, D, A, B, X[2 ], S4[2], MD5::T[62]);
        II(B, C, D, A, X[9 ], S4[3], MD5::T[63]);
        printf("%x\n", A);
        print("\n");
       //print(B);
        //print("\n");
        //print(C);
        //print("\n");
        //print(D);
        print("\n\n");
        /* Then perform the following additions. (That is increment each
        of the four registers by the value it had before this block
        was started.) */
        A += AA;
        B += BB;
        C += CC;
        D += DD;
    }
}

std::string MD5::print_result(){
	char* result = (char*)malloc(16);
	memcpy((char*)result, &A, sizeof(uint32));
    memcpy((char*)result + sizeof(uint32), &B, sizeof(uint32));
    memcpy((char*)result + 2 * sizeof(uint32), &C, sizeof(uint32));
    memcpy((char*)result + 3 * sizeof(uint32), &D, sizeof(uint32));
    
	//char buf[2*RESULT_SIZE+1];
	///buf[2*RESULT_SIZE] = 0;
	//for (int i = 0; i < RESULT_SIZE; i++)
	//	sprintf(buf+i*2, "%02x", result[i]);
	//std::cout << "\n\n" <<  std::string(buf);
	auto res =  std::string(result);
	//print_data_binary((uint8*)result, 16);
	free(result);
	return res;
}
