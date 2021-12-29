#include "Sha.h"

class HashingManager{
public:
	HashingManager() = delete;
	void perform_hash_test(std::string&& input, std::string&& expected);
};
