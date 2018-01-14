#include <iostream>
#include <vector>
#include <allocator>
#include <ext\poll_allocator.h>

using namespace std;

template <typename Alloc> 
void cookie_test(Alloc alloc, size_t n) {

	typename Alloc::value_type *p1, *p2, *p3;

	p1 = alloc.allocate(n);
	p2 = alloc.allocate(n);
	p3 = alloc.allocate(n);

	cout << p1 << "  " << p2 << "  " << p3 << endl;

	alloc.deallocate(p1, sizeof(typename Alloc::value_type));
	alloc.deallocate(p2, sizeof(typename Alloc::value_type));
	alloc.deallocate(p3, sizeof(typename Alloc::value_type));
}

int main (int argc, char** argv) {

	cout << sizeof(int) << endl;

	vector<int, __gnu_cxx::__pool_alloc<int>> vecPool;
	cookie_test(__gnu_cxx::__pool_alloc<int>(), 1);

	vector<int, allocator<int>> vec;
	cookie_test(allocator<int>(), 1);

	return 0;
}