#include <stdlib.h>
#include <stdio.h>
#include <complex>
#include <memory>
#include <ext/pool_allocator.h>

using namespace std;

int main(int argc, char** argv) {

	//1.
	void* p1 = malloc(512); //allocating 512 bytes

	free(p1);
	/*
	printf("%d bytes a char\n", sizeof(char));	
	printf("how many char? \n");
	
	size_t count;
	scanf("%d", &count);
	
	char *buffer = (char*) malloc(count);
	if (buffer == NULL) exit(1);

	for(int i = 0; i < count; i++) {
		buffer[i] = rand()%26 + 'a'; 
	}
	
	buffer[count] = '\0';
	
	printf("%s\n", buffer);

	free(buffer);
	*/

	complex<int> *p2 = new complex<int>;
	delete p2;	
	
	//3. c++ functions	
	void* p3 = ::operator new(512);
	::operator delete(p3);

	//4.allocator
	#ifdef __GNUC__
	printf("this is a gnuc compiler");
	#endif	

	#ifdef __GNUC__
	//call through tmp object 
	void* p4 = allocator<int>().allocate(7);
	allocator<int>().deallocate((int*)p4, 7);

	void* p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
	__gnu_cxx::__pool_alloc<int>().deallocate((int*)p5, 9);

	#endif

	return 0;
} 



