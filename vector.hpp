#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "vector_iterator.hpp"

//https://en.cppreference.com/w/cpp/header/vector copier le header class template
//iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.

//vector is a sequence container that encapsulates dynamic size arrays
namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {

public:
	typedef T value_type;
	typedef value_type* pointer_type;
	typedef value_type& reference_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::size_type size_type; //double check

protected:
	//type
	value_type * content;
	size_t size;
	size_t capacity;

public:
	// 4 constructors required: default/fill/range/copy
	// default (1)	
	explicit vector (const allocator_type& alloc = allocator_type()) : content(NULL), size(0), capacity(0) {(void)alloc;std::cerr << "Default Allocator\n";}
	// fill (2)	
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
		size = n;
		content = alloc(n * sizeof(value_type)));
		for (int i = 0; i < n; i++)
			content[n] = val;
		std::cerr << "Fill Allocator\n";
		std::cerr << content[0];
	}
	// range (3)	
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
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
	~vector(){delete [] content;}

private:
	
};

}

#endif
