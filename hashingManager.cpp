#include "mybits.h"
#include "types.h"
#include "mymacros.h"

#include "HashingManager.h"

void HashingManager::perform_hash_test(std::string&& input, std::string&& expected){
	SHA sasha;
	sasha.init();
	sasha.update((uint8*)input.c_str(), input.length());
	sasha.final();
	if(expected == sasha.print_result()){
		print("\npassed\n");
	}
	else
		print("\nnot passed\n");
}