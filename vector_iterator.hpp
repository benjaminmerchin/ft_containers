#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "vector.hpp"

namespace ft {

template<typename T>
class vector_iterator {
public:
	typedef T value_type;
	typedef value_type* pointer_type;
	typedef value_type& reference_type;

	vector_iterator() : pointer(NULL) {}
	vector_iterator(pointer_type ptr) : pointer(ptr) {}
	vector_iterator(vector_iterator const & src) : pointer(src.ptr) {}

	vector_iterator& operator++() {
		pointer++;
		return *this;
	}

	vector_iterator operator++(int) {
		vector_iterator iterator = *this;
		++(*this);
		return iterator;
	}

	vector_iterator& operator--() {
		pointer--;
		return *this;
	}

	vector_iterator operator--(int) {
		vector_iterator iterator = *this;
		--(*this);
		return iterator;
	}

	reference_type operator[](int index) {return *(pointer + index);}
	pointer_type operator->() {return pointer;}
	pointer_type operator*() {return *pointer;}

	bool operator==(const vector_iterator& other) const {return pointer == other.pointer;}
	bool operator!=(const vector_iterator& other) const {return !(*this == other);}

private:
	pointer_type pointer;
};

}

#endif