#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

class A {
public:
	int id;
	
	A(int i):id(i) {
		cout << "ctor : this " << this << " id :" << id << endl; 
	}
	
	~A() {
		cout << "dtor : " << this << endl;
	}
};

int main(int argc, char** argv) {
	
	string* pstr = new string;
	cout << "str == " << *pstr << endl;

	//pstr->string::string("test");  //string is typedef : basic_string<char>
	//pstr->basic_string<char>::basic_string<char>("test");
	//pstr->~string();

	A* pA = new A(1);
	
	//pA->A::A(3); //can not call ctor directly
	new(pA)A(3);	
	pA->A::~A();
	
	delete pA;
	delete pstr;
	
	return 0;
}
