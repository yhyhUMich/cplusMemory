#include <iostream>
#include <vector>
#include <memory>
#include <ext/pool_allocator.h>

using namespace std;

class test {
	int64_t a;
	int32_t b;	
};

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

	cout << sizeof(int64_t) << endl;

	vector<int, __gnu_cxx::__pool_alloc<int>> vecPool;
	cookie_test(__gnu_cxx::__pool_alloc<int64_t>(), 1);

	vector<int, allocator<int>> vec;
	cookie_test(allocator<test>(), 1);

	return 0;
}
