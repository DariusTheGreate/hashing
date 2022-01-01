#ifndef _MD5_
#define _MD5_

class MD5{
private:
	static const uint32 RESULT_SIZE = (256/8);//32
	static const uint32 MD5_BLOCK_SIZE = (512/8);
public:
	void init();
	void update(const uint8* message, uint32 len);
	void final();
	void transform(const unsigned char *message, uint32 block_nb);
	std::string print_result();
	uint32 len;
	uint8 block[2*MD5_BLOCK_SIZE];


	static const uint32 T[];
	uint8 result[RESULT_SIZE];
	uint32 A,B,C,D;
};

#endif