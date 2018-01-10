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

class Bad {};

class Foo {
public:
	int i; 
	Foo(): i(0) {};
	Foo(int id) : i(id) {
		throw Bad(); 
	}

	static void* operator new(size_t size) {
		cout << "new 1" << endl;
		return malloc(size); 
	}
	static void* operator new(size_t size, void* start) {
		cout << "new 2" << endl;
		return start;
	}
	static void* operator new(size_t size, long extra) {
		cout << "new 3" << endl;
		return malloc(size+extra); 
	}
	static void* operator new(size_t size, long extra, char init) {
		cout << "new 4" << endl;
		return malloc(size+extra); 
	}
	
	static void operator delete(void* ptr, size_t size) {
		cout << "oper delete(void*, size_t)" << endl;
		return free(ptr);
	}
	static void operator delete(void* ptr, void* ptr2) {
		cout << "oper delete(void*, void*)" << endl;
		return free(ptr);
	}
	
};

int main (int argc, char** argv) {
	
	Foo start;
	Foo* p1 = new Foo;
	Foo* p2 = new(&start) Foo;
	Foo* p3 = new(100) Foo;
	Foo* p4 = new(100, 'a') Foo;

	delete p1;	
	
	Foo* p5 = new(&start) Foo(10);
	
	return 0; 
}


