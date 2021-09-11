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

template<class T, class Allocator = std::allocator<T> >
class vector {
public:
	typedef T value_type;
	typedef value_type* pointer_type;
	typedef value_type& reference_type;

/* -------------------------------------------------- */
/*              CONSTRUCTOR / DESTRUCTOR              */
/* -------------------------------------------------- */

	//4 constructors required : empty/fill/range/copy
	vector() : content(NULL), size(0), capacity(0) {
		std::cout << "ft::vector constructed" << std::endl;
	}
	vector(T const src){(void)src;}
	~vector(){}

// default (1)	
// explicit vector (const allocator_type& alloc = allocator_type());
// fill (2)	
// explicit vector (size_type n, const value_type& val = value_type(),
//                  const allocator_type& alloc = allocator_type());
// range (3)	
// template <class InputIterator>
//          vector (InputIterator first, InputIterator last,
//                  const allocator_type& alloc = allocator_type());
// copy (4)	
// vector (const vector& x);

/* -------------------------------------------------- */
/*                      OPERATOR                      */
/* -------------------------------------------------- */

/* -------------------------------------------------- */
/*                 GETTERS / SETTERS                  */
/* -------------------------------------------------- */

/* -------------------------------------------------- */
/*                  MEMBER FUNCTIONS                  */
/* -------------------------------------------------- */


protected:
	//type
	T * content;
	size_t size;
	size_t capacity;
};

}

#endif