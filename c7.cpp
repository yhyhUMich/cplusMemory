#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

//array new array delete

class A {
public:
	int id;

	A():id(0) {
		cout << "default ctor : this " << this << " id :" << id << endl; 
	};
	
	A(int i):id(i) {
		cout << "ctor : this " << this << " id :" << id << endl; 
	}
	
	~A() {
		cout << "dtor : " << this << endl;
	}
};

int main(int argc, char** argv) {
	
	const int size = 10;

	A* buf = new A[size];
 	A* tmp = buf;

	cout << "buf = " << buf << " tmp = " << tmp << endl;

	for(int i = 0; i < size; i++) {
		new(tmp++)A(i);
	}	

	cout << "buf = " << buf << " tmp = " << tmp << endl;
	
	delete[] buf; //delete buf : wrong, self define object must use delete[]
	
	int* pi = new int[10];
	delete pi; //delete[] pi : same because int doesn't have dtor
			
	return 0;
}
