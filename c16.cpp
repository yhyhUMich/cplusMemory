#include <new>
#include <iostream>
#include <cassert>

using namespace std;

void noMoreMemory() {
	cerr << "our of memory";
	
	//assert(0);
	abort();
}

int main (int argc, char** argv) {

	set_new_handler(noMoreMemory);
	int *p = new int[10000000000];
	assert(p);
	
	p = new int [100000000];
	assert(p);

	return 0;
}

