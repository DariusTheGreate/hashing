#include "Sha.h"

#include "MD5.h"

class HashingManager{
public:
	void perform_hash_test_sha(std::string&& input, std::string&& expected);
	void perform_hash_test_md5(std::string&& input, std::string&& expected);
};
