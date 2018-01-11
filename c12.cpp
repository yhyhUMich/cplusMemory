#include <cstddef>
#include <iostream>

using namespace std;

class Screen {
public:
	Screen(int x) : i(x) {}
	inline int get() {return i; }

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

void* Screen::operator new(size_t size) {
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
}

void Screen::operator delete(void* ptr, size_t size) {

	(static_cast<Screen*>(ptr))->next = freeStore;
	freeStore = static_cast<Screen*> (ptr);
}

int main (int argc, char** argv) {
	cout << "size of Screen " << sizeof(Screen) << endl; 
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
}



