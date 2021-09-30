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
	std::vector<int/*, MyAlloc<int> */> a;
	std::cout << "size:" << a.size() << "\tcapacity:" << a.capacity() << "\tmax_size:" << a.max_size() << std::endl;
	a.push_back(time(0)%3);
	a.push_back(time(0)%15);
	a.push_back(time(0)%10);
	a.push_back(time(0)%9);
	a.push_back(time(0)%7);

	typedef std::vector<int>::iterator iterator;

	for (iterator it_a = a.begin(); it_a != a.end(); ++it_a) 
		std::cout << *it_a << ' ';
	std::cout << std::endl;
	std::cout << "size:" << a.size() << "\tcapacity:" << a.capacity() << "\taddress:" << &a << std::endl;
	a.resize(4);
	std::cout << "size:" << a.size() << "\tcapacity:" << a.capacity() << "\taddress:" << &a << std::endl;

	std::cout << "------------------\n";

	ft::vector<int> b(2, 3);
	//std::cout << b[0] << ' ' << b[1] << std::endl;
	std::cout << "size:" << b.size() << "\tcapacity:" << b.capacity() << "\tmax_size:" << b.max_size() << std::endl;
	b.push_back(time(0)%3);
	b.push_back(time(0)%14);
	b.push_back(time(0)%10);
	std::cout << "size:" << b.size() << "\tcapacity:" << b.capacity() << std::endl;
	//std::cout << b[0] << ' ' << b[1] << ' ' << b[2] << ' ' << b[3] << ' ' << b[4] << std::endl;
	for (unsigned int i = 0; i < b.size(); i++)
		std::cout << b[i] << ' ';
	std::cout << std::endl;
	for (ft::vector<int>::iterator it = b.begin() ; it != b.end(); ++it)
    	std::cout << *it << ' ';
	std::cout << std::endl;

	std::cout << "------------------\n";

	ft::vector<int> c(2, 3);
	c.assign(7, 100);
	for (unsigned int i = 0; i < c.size(); i++)
		std::cout << c[i] << ' ';
	std::cout << std::endl;
	
	int myints[] = {1776,7,4};(void)myints;
	ft::vector<int> d;
	ft::vector<int>::iterator it;
	//it = c.begin() + 1;
	//d.

	return 0;
}
