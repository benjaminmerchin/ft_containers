#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

#include <memory>
#include <iostream>
#include <string>
//#include "vector.hpp"

namespace ft {

template<typename T>
class RandomAccessIterator {
public:
	typedef std::forward_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;

	RandomAccessIterator() : _pointer(NULL) {}
	RandomAccessIterator(value_type * ptr) : _pointer(ptr) {}
	RandomAccessIterator(RandomAccessIterator const & src) : _pointer(src._pointer) {}
	~RandomAccessIterator() {}

protected:
	value_type * _pointer;

public:
	RandomAccessIterator& operator++() {
		_pointer++;
		return *this;
	}

	RandomAccessIterator operator++(int) {
		RandomAccessIterator it = *this;
		++(*this);
		return it;
	}

	RandomAccessIterator& operator--() {
		_pointer--;
		return *this;
	}

	RandomAccessIterator operator--(int) {
		RandomAccessIterator it = *this;
		--(*this);
		return it;
	}

};

}

#endif