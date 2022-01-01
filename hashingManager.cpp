#include "mybits.h"
#include "types.h"
#include "mymacros.h"

#include "HashingManager.h"

void HashingManager::perform_hash_test_sha(std::string&& input, std::string&& expected){
	std::cout << "input -> " << input << "\n";
	SHA sasha;
	sasha.init();
	sasha.update((uint8*)input.c_str(), input.length());
	sasha.final();
	auto res = sasha.print_result();
	if(expected == res){
		std::cout << "expected -> " << (expected) << "\n";
		std::cout << "res -> " << (res) << "\n";
		print("passed\n\n");
	}
	else
		print("\nnot passed\n");
}


void HashingManager::perform_hash_test_md5(std::string&& input, std::string&& expected){
	MD5 sasha;
	sasha.init();
	sasha.update((uint8*)input.c_str(), input.length());
	sasha.final();
	if(expected == sasha.print_result()){
		print("\npassed\n");
	}
	else
		print("\nnot passed\n");
}
