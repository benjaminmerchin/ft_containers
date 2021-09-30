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
	//typedef ft::vector::value_type value_type;
	typedef value_type* pointer_type;
	typedef value_type& reference_type;

	vector_iterator() : _pointer(NULL) {}
	vector_iterator(value_type * ptr) : _pointer(ptr) {}
	vector_iterator(vector_iterator const & src) : _pointer(src._pointer) {}
	~vector_iterator() {}

	vector_iterator & operator=(vector_iterator const & rhs) {_pointer = rhs._pointer;return *this;}

	vector_iterator& operator++() {
		_pointer++;
		return *this;
	}

	vector_iterator operator++(int) {
		vector_iterator iterator = *this;
		++(*this);
		return iterator;
	}

	vector_iterator& operator--() {
		_pointer--;
		return *this;
	}

	vector_iterator operator--(int) {
		vector_iterator iterator = *this;
		--(*this);
		return iterator;
	}

	value_type& operator[](int index) {return *(_pointer + index);}
	value_type* operator->() {return _pointer;}
	value_type& operator*() {return *_pointer;}

	bool operator==(const vector_iterator& other) const {return _pointer == other._pointer;}
	bool operator!=(const vector_iterator& other) const {return !(*this == other);}

private:
	value_type * _pointer;
};

template<typename T>
std::ostream & operator<<(std::ostream & o, vector_iterator<T> & rhs) {
	o << *rhs;
	return o;
}

}

#endif

//ft::vector<int, std::__1::allocator<int> >::pointer_type							int *
//ft::vector<int, std::__1::allocator<int> >::iterator								vector_iterator<vector<int> >