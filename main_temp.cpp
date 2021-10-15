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

void ft_reverse_iterator() {
	std::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;
															// ? 0 1 2 3 4 5 6 7 8 9 ?
	iter_type from (myvector.begin());                     //   ^
															//         ------>
	iter_type until (myvector.end());                      //                       ^
															//
	std::reverse_iterator<iter_type> rev_until (from);     // ^
															//         <------
	std::reverse_iterator<iter_type> rev_from (until);     //                     ^

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	std::cout << '\n';	
}

void ft_reverse_iterator_2() {
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_iterator = myvector.rend();

	rev_iterator -= 4;

	std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';
}

void ft_reverse_iterator_3() {
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_iterator;

	rev_iterator = myvector.rend() - 3;

	std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';
}

void ft_reverse_iterator_relational_operator() {
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;
														// ? 9 8 7 6 5 4 3 2 1 0 ?
	iter_type from (myvector.begin());                     //   ^
														//         ------>
	iter_type until (myvector.end());                      //                       ^
														//
	std::reverse_iterator<iter_type> rev_until (from);     // ^
														//         <------
	std::reverse_iterator<iter_type> rev_from (until);     //                     ^

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	//std::cout << '\n';

	std::reverse_iterator<iter_type> rev_it;
	rev_it = 3 + myvector.rbegin();

	std::cout << " - 4th elem: " << *rev_it << '\n';
}

void ft_reserve() {
	std::vector<int>::size_type sz;

	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	std::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void ft_swap_mli() {
	ft::vector<int> foo(3, 15);
	ft::vector<int> bar(5, 42);
	ft::vector<int>::const_iterator it_foo = foo.begin();
	ft::vector<int>::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	//printSize(foo);
	std::cout << "bar contains:" << std::endl;
	//printSize(bar);

	foo.swap(bar);
	/*

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	//printSize(foo);
	std::cout << "bar contains:" << std::endl;
	//printSize(bar);

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
	*/

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

	ft_reverse_iterator();
	std::cerr << "myvector: 9 8 7 6 5 4 3 2 1 0" << std::endl;
	ft_reverse_iterator_2();
	std::cerr << "rev_iterator now points to: 3" << std::endl;
	ft_reverse_iterator_3();
	std::cerr << "myvector.rend()-3 points to: 2" << std::endl;
	ft_reverse_iterator_relational_operator();
	std::cerr << "myvector: 9 8 7 6 5 4 3 2 1 0 - 4th elem: 6" << std::endl;
	ft_reserve();
	
	ft_swap_mli();

	return 0;
}
