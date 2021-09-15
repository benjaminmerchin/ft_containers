#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "vector_iterator.hpp"
#include "utils.cpp"

//https://en.cppreference.com/w/cpp/header/vector copier le header class template
//iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.

//vector is a sequence container that encapsulates dynamic size arrays
namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {

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
	allocator_type alloc_type; //ie:        std::allocator<T> alloc_type;
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
		capacity = n;
		(void)alloc;(void)val;
		//content = alloc(n * sizeof(value_type));
		content = alloc_type.allocate(n);
		for (size_type i = 0; i < n; i++)
			content[n] = val;
		std::cerr << "Fill Allocator\n";
		std::cerr << content[0] << std::endl;
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
	~vector(){delete [] content;}

private:
	
};

}

#endif
