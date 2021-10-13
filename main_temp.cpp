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

void ft_insert() {
	std::vector<int> myvector (3,100);
	std::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	std::vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
	std::cout << ' ' << *it;
	std::cout << '\n';
}

void ft_swap() {
	int x=10, y=20;                              // x:10 y:20
	std::swap(x,y);                              // x:20 y:10

	std::vector<int> foo (4,x), bar (6,y);       // foo:4x20 bar:6x10
	std::swap(foo,bar);                          // foo:6x10 bar:4x20

	std::cout << "foo contains:";
		for (std::vector<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
}

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
	ft::vector<int>::iterator iter = c.begin();
	//ft::vector<int>::const_iterator iter = c.end();
	for (unsigned int i = 0; i < c.size(); i++)
		std::cout << c[i] << ' ';
	std::cout << std::endl;

	int myints[] = {1776,7,4};(void)myints;
	ft::vector<int> d;
	//it = c.begin() + 1;
	//d.
	std::cout << "------------------\n"; //erase

	std::vector<int> myvector;
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector.push_back(i);
	// erase the 6th element
	myvector.erase (myvector.begin()+5);
	// erase the first 3 elements:
	myvector.erase (myvector.begin(),myvector.begin()+3);
	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	std::cout << "------------------\n"; //insert
	//std::cerr << it << ' ' << *it << ' ' << &it << std::endl;

	ft::vector<int> myvector_2 (3,100);
	myvector_2.reserve(1000); // ERROR BETWEEN WITH THE ADDRESS OF it IF I REMOVE THIS
	ft::vector<int>::iterator it;
	//ft::vector<int> myvector_2;
	//for (int i=1; i<=3; i++)
	//	myvector_2.push_back(i);
	std::cout << "A " << &it[0] << std::endl;
	it = myvector_2.begin();
	std::cout << "B " << &it[0] << std::endl;
	it = myvector_2.insert ( it , 200 );
	std::cout << "C " << &it[0] << std::endl;

	myvector_2.insert (it,2,300);
	std::cout << "D " << &it[0] << std::endl;

	// "it" no longer valid, get a new one:
	it = myvector_2.begin() + 1;

	ft::vector<int> anothervector (myvector_2.begin(), myvector_2.end());
	myvector_2.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector_2.insert (myvector_2.begin(), myarray, myarray+3);

	std::cout << "myvector_2 contains:";
		for (it=myvector_2.begin(); it<myvector_2.end(); it++)
	std::cout << ' ' << *it;
	std::cout << '\n';

	ft_insert();
	std::cerr << "myvector contains: 501 502 503 300 300 400 400 200 100 100 100" << std::endl;
	ft_swap();
	std::cerr << "foo contains: 10 10 10 10 10 10" << std::endl;


	std::cerr << "is_integral w/ float: " << std::boolalpha << ft::is_integral<float>::value << std::endl; 
	std::cerr << "is_integral w/ int: " << std::boolalpha << ft::is_integral<int>::value << std::endl;

	return 0;
}

/*
./vector.hpp:185:17: error: no viable conversion from 'ft::vector<int, std::__1::allocator<int> >::iterator'
      (aka 'vector_iterator<int>') to 'int'

ft::vector<int, std::__1::allocator<int> >::iterator
vector_iterator<int>
int

int                      aka ft::vector<int, std::__1::allocator<int> >::value_type
ft::vector_iterator<int> aka typename ft::enable_if<!ft::is_integral<vector_iterator<int> >::value, vector_iterator<int> >::type
*/
