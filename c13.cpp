#include <iostream>

class Airplane {

private:
	struct AirplaneRep {
		unsigned long miles;
		char type;
	};

private:
	//imbeded pointer
	union { 
		AirplaneRep rep;
		Airplane* next;
	};

public:
	unsigned long getMiles() {
		return rep.miles;
	}

	char getType() {
		return rep.type;
	}

	void set(unsigned long m, char t) {
		rep.miles = m;
		rep.type = t;
	}

public:
	static void* operator new (size_t size);
	static void operator delete(void* ptr, size_t size);

private:
	static const int BLOCK_SIZE;
	static Airplane* headOfFreeList;
};

Airplane* Airplane::headOfFreeList = 0;
const int Airplane::BLOCK_SIZE = 512;

void* Airplane::operator new (size_t size) {
	//in case of inheritance happens 
	if (size != sizeof(Airplane)) {
		return ::operator new(size);
	}

	Airplane* p = headOfFreeList;

	if (p) {
		headOfFreeList = p->next;
	}
	else {
		Airplane *newBlock = static_cast<Airplane*>
			(::operator new(BLOCK_SIZE * sizeof(Airplane)));

		for (int i = 1; i < BLOCK_SIZE-1; i++) {
			newBlock[i].next = &newBlock[i+1];
		}

		newBlock[BLOCK_SIZE-1].next = 0;

		p = newBlock;
		headOfFreeList = &newBlock[1];
	}

	return p;
}

void Airplane::operator delete (void* ptr, size_t size) {

	if(ptr == 0) {
		return;
	}

	if(size != sizeof(Airplane)) {
		::operator delete(ptr);
		return;
	}

	Airplane* carcass = 
		static_cast<Airplane* >(ptr);

	carcass->next = headOfFreeList;
	headOfFreeList = carcass;
}

int main (int argc, char** argv) {

	cout << sizeof(Airplane) << endl;
	cout << sizeof(unsigned long) << endl;
	cout << sizeof(short) << endl;

	size_t const N = 100;
	Airplane* P[N];

	for(int i = 0; i < N; i++) {
		P[i] = new Airplane;
	}

	p[1]->set(1000, 'A');
	p[5]->set(2000, 'B');
	p[9]->set(5000, 'C');

	for(int i = 0; i < 10; i++) {
		cout << p[i] << endl;
	}

	for(int i = 0; i < N; i++) {
		delete p[i];
	}

	return 0;
}


