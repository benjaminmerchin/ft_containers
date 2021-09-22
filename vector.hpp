#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
//#include <vector>
#include "vector_iterator.hpp"
#include "utils.cpp"

//https://en.cppreference.com/w/cpp/header/vector copier le header class template
//iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.

//reuse the functions from the allocator_traits: allocate, deallocate, construct, destroy & max_size
//vector is a sequence container that encapsulates dynamic size arrays
namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector/* : public std::vector<T>*/ {

public:
	//list of the typedef required: https://cplusplus.com/reference/vector/vector/
	typedef T                                        value_type;
	typedef value_type*                              pointer_type;
	typedef value_type&                              reference_type;
	typedef Alloc                                    allocator_type;
	typedef typename allocator_type::reference       reference;
	typedef typename allocator_type::const_reference const_reference;
	// typedef implementation-defined                   iterator;
	// typedef implementation-defined                   const_iterator;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	// typedef std::reverse_iterator<iterator>          reverse_iterator;
	// typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

protected:
	allocator_type alloc_type; //ie:        std::allocator<T> alloc_type; basically we store the Alloc which is a class
	//std::allocator<T> alloc_type;			
	pointer_type content;
	size_type sz;
	size_type cap; //toujours une puissance de 2

public:
//MEMBER FUNCTIONS
	// 4 constructors required: default/fill/range/copy
	// default (1)
	explicit vector (const allocator_type& alloc = allocator_type()) : content(NULL), sz(0), cap(0) {(void)alloc;std::cerr << "Default Allocator\n";}
	// fill (2)
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
		sz = n;
		cap = n;
		(void)alloc;(void)val;
		//content = alloc(n * sizeof(value_type));
		content = alloc_type.allocate(n);
		for (size_type i = 0; i < n; i++)
			content[n] = val;
		std::cerr << "Fill Allocator\n";
		//std::cerr << content[0] << std::endl;
	}
	// range (3)
	template <class InputIterator>
	//vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) 
	vector (typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type())
	{
		(void)first;
		(void)last;
		(void)alloc;
		std::cerr << "Range Allocator\n";
	}
	// copy (4)
	vector (const vector& x) {
		(void)x;
		std::cerr << "Copy Allocator\n";
	}
	~vector() {delete [] content;}

//ITERATORS
// begin Return iterator to beginning (public member function )
// end Return iterator to end (public member function )
// rbegin Return reverse iterator to reverse beginning (public member function )
// rend Return reverse iterator to reverse end (public member function )

//CAPACITY
	size_type size() const {return sz;}
	size_type max_size() const {return alloc_type.max_size();}
	size_type capacity() const {return cap;}
	bool empty() const {return sz == 0 ? true : false;}
	void reserve(size_type n) {add_space(n - cap);}
	void resize(size_type n, value_type val = value_type()) {
		if (n > sz)
			sz = n;
		add_space(n - cap);
		for (size_type i = sz; i < n; i++)
			content[n] = val;
	}

//ELEMENT ACCESS
	reference operator[] (size_type n) {return content[n];}
	const_reference operator[] (size_type n) const {return content[n];}
	reference at (size_type n) {return content[n];}
	const_reference at (size_type n) const {return content[n];}
	reference front() {return content[0];}
	const_reference front() const {return content[0];}
	reference back() {return content[sz - 1];}
	const_reference back() const {return content[sz - 1];}

//MODIFIERS
	void push_back(const value_type& val) {
		if (sz == cap) //size is always lower (enough space) or equal
			add_space(1);
		content[sz] = val;
		sz++;
	}
	void pop_back() {sz--;}
	void swap(vector& x) {ft::vector<value_type> temp(x); x = *this; *this = temp;}
	//iterator erase(iterator position);
	//iterator erase(iterator first, iterator last);

//ALLOCATOR
	allocator_type get_allocator() const {return alloc_type;}

//NON-MEMBER FUNCTION OVERLOADS
	// template <class T, class Alloc>
	// bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// swap Exchange contents of vectors (function template )

private:
	void add_space(int n) {
		if (n + sz <= cap) //no need to add space
			return ;
		if (cap == 0)
			cap = 1;
		while (n + sz > cap)
			cap *= 2;
		pointer_type update = alloc_type.allocate(cap);
		for (size_type i = 0; i < sz; i++)
			update[i] = content[i];
		delete [] content;
		content = update;
	}
};

}

#endif
