#include <complex>
#include <stdlib.h>
#include <new>

using namespace std;

int main (int argc, char** argv) {
	
	void* buf = malloc(sizeof(complex<int>) * 3);
	
	complex<int>* pc = new(buf)complex<int>(1,2);
	
	delete pc;
		
	return 0; 
}
