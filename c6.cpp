#include <complex>
#include <stdlib.h>

int main (int argc, char** argv) {

	complex<int>* pca = new complex<int>[3];
	
	delete[] pca;

	return 0; 
}
