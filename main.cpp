#include <iostream>
#include <string>
#include <bitset>
#include <cstring>

#include "types.h"
#include "mybits.h"
#include "mymacros.h"

#include "HashingManager.h"

#include "Sha.h"

int foo(float* f, int* i){
	*f = 5;
	//*i = 5;
	std::cout << f << " " << i << "\n";
	return *i;
}

int main(){
	HashingManager man;
	man.perform_hash_test("abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
	man.perform_hash_test("abcd", "88d4266fd4e6338d13b845fcf289579d209c897823b9217da3e161936f031589");
	man.perform_hash_test("mamka", "46e2b676159a4afba51faa42feaa1db063df130cd27b252266fb1fa53c5d0ef9");
	man.perform_hash_test("loh", "5611e6627047d0d44236ea513e1fbd30c9e50ca97f78445cf91dffd074c868a3");
	man.perform_hash_test("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq", "5407e659164ac6b32caabfeaa8d13767010d21beef2f32fa37ba370b12cb331b");//ok
	man.perform_hash_test("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq", "ee8e658590c9a5e119400a774415a01db104de1ee6e2c29ec69aa73ef46544d2");// not ok when len >= 64
	return 0;
}
