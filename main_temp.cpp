#include "vector.hpp"
#include <vector>

template<typename type>
struct MyAlloc : std::allocator<type> {
	type * allocate(size_t size) {
		return new type[size];
	}
	void deallocate(type * ptr, size_t) {
		delete [] ptr;
	}
};

int main(void) {
	std::vector<int, MyAlloc<int> > a;
	std::cout << "size:" << a.size() << "\tcapacity:" << a.capacity() << std::endl;
	a.push_back(time(0)%3);
	a.push_back(time(0)%15);
	a.push_back(time(0)%10);
	a.push_back(time(0)%9);
	a.push_back(time(0)%7);

	typedef std::vector<int>::iterator iterator;

	for (iterator it_a = a.begin(); it_a != a.end(); ++it_a) 
		std::cout << *it_a << ' ';
	std::cout << std::endl;
	std::cout << "size:" << a.size() << "\tcapacity:" << a.capacity() << std::endl;
	
	std::cout << "------------------\n";

	ft::vector<char> b(2, 'c');
	//std::cout << '@';
	//std::vector<int>::iterator it;

	return 0;
}

