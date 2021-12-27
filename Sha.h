#ifndef _SHA_
#define _SHA_

class SHA{
private:
	static const uint32 RESULT_SIZE = (256/8);//32
	static const uint32 SHA_BLOCK_SIZE = (512/8);
public:
	void init();
	void update(const uint8* message, uint32 len);
	void final();
	void transform(const unsigned char *message, unsigned int block_nb);
	std::string print_result();
	uint32 len;
	uint8 block[2*SHA_BLOCK_SIZE];
	uint32 H[8];

private:
	static const uint32 K[];
	uint8 result[RESULT_SIZE];
};

#endif