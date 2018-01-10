#include <complex>
#include <stdlib.h>
#include <iostream>

using namespace std;

void* myAlloc(size_t size) {
	return malloc(size);
}

void myFree(void* ptr) {
	return free(ptr);
}

inline void* operator new(size_t size) {
	cout << "hang global new() \n"; 
	return myAlloc(size);
}

inline void operator delete(void* ptr) {
	cout << "hang global delete \n";
	myFree(ptr);
}

class Foo {
public:
	static void* operator new(size_t);
	static void operator delete(void*, size_t);
}

int main (int argc, char** argv) {
	
	char* ptr = new char('a');
	delete ptr;
	
	return 0; 
}


