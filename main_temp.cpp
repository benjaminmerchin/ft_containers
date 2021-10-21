#include "vector.hpp"
#include "stack.hpp"
#include <vector>

template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = 1)
{
	std::cout << "size: " << vct.size() << std::endl;
	std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

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
	ft::vector<int> myvector (3,100);
	ft::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	/*
	*/
}

void ft_swap() {
	int x=10, y=20;                             // x:10 y:20
	std::swap(x,y);                              // x:20 y:10

	ft::vector<int> foo (4,x), bar (6,y);       // foo:4x20 bar:6x10
	ft::swap(foo,bar);                          // foo:6x10 bar:4x20

	std::cout << "foo contains:";
		for (ft::vector<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
}

void ft_reverse_iterator() {
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;
															// ? 0 1 2 3 4 5 6 7 8 9 ?
	iter_type from (myvector.begin());                      //   ^
															//         ------>
	iter_type until (myvector.end());                       //                       ^
															//
	ft::reverse_iterator<iter_type> rev_until (from);      // ^
															//         <------
	ft::reverse_iterator<iter_type> rev_from (until);      //                  

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
	iter_type from (myvector.begin());                  //   ^
														//         ------>
	iter_type until (myvector.end());                   //                       ^
														//
	std::reverse_iterator<iter_type> rev_until (from);  // ^
														//         <------
	std::reverse_iterator<iter_type> rev_from (until);  //                     ^

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	//std::cout << '\n';

	std::reverse_iterator<iter_type> rev_it;
	rev_it = 3 + myvector.rbegin();

	std::cout << " - 4th elem: " << *rev_it << '\n';
}

void ft_reserve() {
	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow: ";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << sz << ' ';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "|making bar grow: ";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << sz << ' ';
		}
	}
	std::cout << std::endl;
}

void ft_rbegin() {
	ft::vector<int> myvector (5);  // 5 default-constructed ints

	int i=0;

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void ft_rend() {
	ft::vector<int> myvector (5);  // 5 default-constructed ints

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void ft_constructor() {
	// constructors used in the same order as described above:
	ft::vector<int> first;                // DEFAULT
	ft::vector<int> second (4,100);          // four ints with value 100 FILL
	ft::vector<int> fourth (second);          // COPY
	ft::vector<int> third (second.begin(),second.end());  // RANGE

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	/*
	*/
}

template <class T>
void print_vector(ft::vector<T> myvector) {
	for (unsigned long i=0; i<myvector.size(); ++i)
		std::cout << myvector[i] << ' ';
	std::cout << '\n';
}

void ft_test() {
	ft::vector<int> vct(7);
	ft::vector<int> vct_two(4);
	ft::vector<int> vct_three;
	ft::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	/*
	*/
    ft::vector<char> characters;
 
 
    characters.assign(5, 'a');
	for (unsigned long i=0; i<characters.size(); ++i)
		std::cout << characters[i] << ' ';
	std::cout << '\n';
 
    const std::string extra(6, 'b');
    characters.assign(extra.begin(), extra.end());
	for (unsigned long i=0; i<characters.size(); ++i)
		std::cout << characters[i] << ' ';
	std::cout << '\n';
 
    /*
	characters.assign({'C', '+', '+', '1', '1'});
	for (unsigned long i=0; i<characters.size(); ++i)
		std::cout << characters[i] << ' ';
	std::cout << '\n';
	*/
}

void basic_tests() {
	std::vector<int> a;
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
	std::cout << "------------------\n";

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
	/*
	*/
}

void	checkErase(ft::vector<int> &vct, ft::vector<std::string>::iterator &it) {
	(void)vct;
	(void)it;
	/*
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
	*/
}

void ft_erase_mli(void) {
	/*
	ft::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));
	*/
}

void ft_erase() {
	ft::vector<int> myvector;

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



	//ft_erase_mli();


	ft::vector<int>::iterator it = myvector.begin() + 2;
	(void)it;
}

void test_list() {
	basic_tests();

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
	std::cerr << "making foo grow: 1 2 4 8 16 32 64 128 |making bar grow: 100" << std::endl;
	

	ft_rbegin();
	std::cerr << "myvector contains: 5 4 3 2 1" << std::endl;
	ft_rend();
	std::cerr << "myvector contains: 5 4 3 2 1 " << std::endl;
	ft_constructor();
	std::cerr << "The contents of fifth are: 16 2 77 29" << std::endl;
	ft_insert();
	std::cerr << "myvector contains: 501 502 503 300 300 400 400 200 100 100 100" << std::endl;
	ft_erase();
	std::cerr << "myvector contains: 4 5 7 8 9 10" << std::endl;
	
	/*
	*/
}

void stack_size() {
	ft::stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\t';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\t';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
	std::cerr << "0. size: 0\t1. size: 5\t2. size: 4" << std::endl;
}

void stack_push() {
	ft::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty()) {
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';
	std::cerr << "Popping out elements... 4 3 2 1 0" << std::endl;
}

int main() {
	//test_list();

	//ft_test();
	stack_size();
	stack_push();

	ft::stack<int> mystack;
	ft::stack<int> mystack2;
	std::cout << std::boolalpha << (mystack == mystack2) << std::endl;
	mystack.push(1);
	std::cout << std::boolalpha << (mystack == mystack2) << std::endl;

	return 0;
}
