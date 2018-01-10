#include <complex>
#include <stdio.h>

using namespace std;

//expression new
//calls function operator new()
//operator new() calls malloc

int main (int argc, char** argv) {
	
	complex<int> *pc;
	try {
		printf("%d bytes a complex \n", sizeof(complex<int>));

		void* mem = operator new(sizeof(complex<int>));
		pc = static_cast<complex<int>*>(mem);
		//pc->complex<int>::complex<int>(1,2);
		new(pc)complex<int>(1,2); //placement new
	}
	catch(bad_alloc) {
		printf("bad_alloc happened\n");
		pc = new complex<int>(1,2);
	}
	

	pc->~complex<int>();
	operator delete(pc);

	return 0;
}
