#include <iostream>
#include <string>
#include <cstddef>
#include <cstdlib>

using namespace std;

class alloc {

private:
	struct obj {
		struct obj* next; // embedded pointer
	};

public:
	void* allocate(size_t size);
	void deallocate(void* ptr, size_t size);
private:
	obj* freeStore = nullptr;
	const int CHUNK = 5;
};

void alloc::deallocate(void* ptr, size_t size) {
	(reinterpret_cast<obj*> (ptr))->next = freeStore;
	freeStore = reinterpret_cast<obj*> (ptr);
} 

void* alloc::allocate(size_t size) {
	obj* p;

	if(!freeStore) {
		freeStore = p = reinterpret_cast<obj*> (malloc(CHUNK * size));

		for(int i = 0; i < CHUNK-1; i++) {
			p->next = reinterpret_cast<obj*>(reinterpret_cast<char*> (p) + size);
			p = p->next;
		}

		p->next = nullptr;
	}
	
	p = freeStore;
	freeStore = p->next;
	return p;
}

class Foo {
public:
	long L;
	string str;
	string str2;
	char ch;
	static alloc myAlloc;
public:
	Foo(long l) : L(l) {}
	
	static void* operator new (size_t size) {
		return myAlloc.allocate(size);
	}

	static void operator delete(void* ptr, size_t size) {
		myAlloc.deallocate(ptr, size);
	}
};

alloc Foo::myAlloc;

int main (int argc, char** argv) {
	
	Foo* p[20];
	
	cout << "sizeof Foo " << sizeof(Foo) << endl;
	cout << "sizeof long" << sizeof(long) << endl;
	cout << "sizeof string" << sizeof(string) << endl;
	
	for(int i = 0; i < 20; i++) {
		p[i] = new Foo(i);
		cout << p[i] << " " << p[i]->L << endl;
	}

	for(int i = 0; i < 20; i++) {
		delete p[i];
	}
		
	return 0;
}
