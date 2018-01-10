#include <complex>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class Foo {
public:
	int _id;
	long _data;
	string _str;
public:
	Foo(): _id(0) {
		cout << "default ctor.this = " << this << " id = " << _id << endl;
	}

	Foo(int id): _id(id) {
		cout << "ctor.this = " << this << " id = " << _id << endl;
	}
	
	~Foo() {
		cout << "dtor.this = " << this << " id = " << _id << endl;
	}	

	static void* operator new(size_t);
	static void operator delete(void*, size_t);
	//static void* operator new[](size_t);
	//static void operator delete[](void*, size_t);
};

void* Foo::operator new(size_t size) {
	Foo* p = (Foo*)malloc(size);
	cout << "myalloc" << endl;
	return p;
}

void Foo::operator delete(void* ptr, size_t size) {
	cout << " mydelete" << endl;
	free(ptr);
}

int main (int argc, char** argv) {

	cout << "size of Foo " << sizeof(Foo) << endl;	

	Foo* p = new Foo(5);
	delete p;
	
	Foo* p2 = ::new Foo(7);
	::delete p2;
		
	return 0; 
}


