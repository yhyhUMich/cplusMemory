#include <iostream>
#include <cstdlib>
#include <list>
#include <memory>
#include <ext/pool_allocator.h>

using namespace std;

static long long countNew = 0;
static long long timesNew = 0;

void* myAlloc(size_t size) {
	return malloc(size);
}

void myFree(void* ptr) {
	free(ptr);
}

inline void* operator new(size_t size) {
	//cout << "hang global new \t" << size << endl;
	countNew += size;
	++timesNew;
	return myAlloc(size);
}

inline void* operator new[](size_t size) {
	return myAlloc(size);
}

inline void operator delete(void* ptr, size_t size) {
	myFree(ptr);
}

inline void operator delete[](void* ptr, size_t size) {
	myFree(ptr);
}

template<typename T>
using listPool = list<T, __gnu_cxx::__pool_alloc<T>>;

int main(int argc, char** argv) {
	
	countNew = 0;
	timesNew = 0;

	list<double> lst;
	
	cout << "double \t" << sizeof(double) << endl;
	cout << "ptr \t" << sizeof(void*) << endl;

	for (int i = 0; i < 1000000; i++) {
		lst.push_back(i);
	}

	cout <<"::countNew = " << countNew << endl;
	cout <<"::timesNew = " << timesNew << endl; 
	
	countNew = 0;
	timesNew = 0;

	listPool<double> lst2;
	
	for(int i = 0; i < 1000000; i++) {
		lst2.push_back(i);
	}
	
	cout << "::countNew = " << countNew << endl;
	cout << "::timesNew = " << timesNew << endl;

	return 0;
} 
