#include <cstddef>
#include <iostream>

using namespace std;

class Screen {
public:
	Screen(int x) : i(x) {};
	int get() {return i; }

	static void* operator new (size_t size);
	static void operator delete(void* ptr, size_t size); 

private:
	Screen* next;
	static Screen* freeStore;
	static const int screenChunk;

private:
	int i;
};

Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

static void* Screen::operator new(size_t size) {
	Screen* p;

	if(!freeStore) {
		//since the linked list is empty, we would declare
		//a chunk of memory

		size_t chunk = screenChunk * size; //new Screen : size = sizeof(Screen)
		freeStore = p = 
			reinterpret_cast<Screen*>(new char[chunk]);

		for(; p != &freeStore[screenChunk-1]; p++)
			p->next = p+1;

		p->next = 0;
	}	

	p = freeStore;
	freeStore = freeStore->next;
	return p;
};

static void Screen::operator delete(void* ptr, size_t size) {

	(static_cast<Screen*>(ptr))->next = freeStore;
	freeStore = static_cast<Screen*> (ptr);
};

int main (int argc, char** argv) {
	cout << "size of Screen " << sizeof(Screen) << endl; 
	cout << "size of int " << sizeof(int) << endl; 
	cout << "size of pointer" << sizeof(void*) << endl; 
	size_t const N = 100;

	Screen* p[N];

	for(int i = 0; i < N; i++) {
		p[i] = new Screen(i);
	}

	for(int i = 0; i < 10; i++) {
		cout << p[i] << endl;
	}

	for(int i = 0; i < N; i++) {
		delete p[i];
	}

	Screen* p2[N];

	for(int i = 0; i < N; i++) {
		p2[i] = ::new Screen(i);
	}

	for(int i = 0; i < 10; i++) {
		cout << p2[i] << endl;
	}

	for(int i = 0; i < N; i++) {
		::delete p2[i];
	}

	return 0;
}



