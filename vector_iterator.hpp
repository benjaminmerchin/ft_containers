#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "vector.hpp"
#include "RandomAccessIterator.hpp"

namespace ft {

template<typename T>
class vector_iterator : public ft::RandomAccessIterator<T> {
public:
	typedef T value_type;
	//typedef ft::vector::value_type value_type;
	typedef std::forward_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;
	typedef value_type* pointer_type;
	typedef value_type& reference_type;
	typedef RandomAccessIterator<T> rai;

	vector_iterator() : rai(NULL) {}
	vector_iterator(value_type * ptr) : rai(ptr) {}
	vector_iterator(vector_iterator const & src) : rai(src) {}
	~vector_iterator() {}

	vector_iterator & operator=(vector_iterator const & rhs) {rai::_pointer = rhs._pointer;return *this;}

	vector_iterator& operator++() { rai::operator++(); return *this; }
	vector_iterator operator++(int) { return rai::operator++(0); }
	vector_iterator& operator--() { rai::operator--(); return *this; }
	vector_iterator operator--(int) { return rai::operator--(0); }

	value_type& operator[](int index) {return *(rai::_pointer + index);}
	value_type* operator->() {return rai::_pointer;}
	value_type& operator*() {return *rai::_pointer;}

	bool operator==(const vector_iterator& other) const {return rai::_pointer == other._pointer;}
	bool operator!=(const vector_iterator& other) const {return !(*this == other);}
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