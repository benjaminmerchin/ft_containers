#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <memory>
#include <iostream>
#include <string>

namespace ft {

template<typename T>
class vector_iterator {
public:
	typedef T value_type;
	typedef std::forward_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef value_type& reference;

	vector_iterator() : _pointer(NULL) {}
	vector_iterator(value_type * ptr) : _pointer(ptr) {}
	vector_iterator(vector_iterator const & src) : _pointer(src._pointer) {}
	~vector_iterator() {}
	vector_iterator & operator=(vector_iterator const & rhs) {_pointer = rhs._pointer; return *this;}
	value_type * get_ptr(void) const {return _pointer;}
	operator vector_iterator<value_type const>() const {return vector_iterator<value_type const>(_pointer);}

protected:
	value_type * _pointer;

public:
	vector_iterator& operator++() {
		_pointer++;
		return *this;
	}

	vector_iterator operator++(int) {
		vector_iterator it = *this;
		++(*this);
		return it;
	}

	vector_iterator& operator--() {
		_pointer--;
		return *this;
	}

	vector_iterator operator--(int) {
		vector_iterator it = *this;
		--(*this);
		return it;
	}

	value_type& operator[](int index) {return *(_pointer + index);}
	value_type* operator->() {return _pointer;}
	value_type& operator*() {return *_pointer;}

	bool operator==(const vector_iterator& other) const {return _pointer == other._pointer;}
	bool operator!=(const vector_iterator& other) const {return _pointer != other._pointer;}
	bool operator<(const vector_iterator& other) const {return _pointer < other._pointer;}
	bool operator<=(const vector_iterator& other) const {return _pointer <= other._pointer;}
	bool operator>(const vector_iterator& other) const {return _pointer > other._pointer;}
	bool operator>=(const vector_iterator& other) const {return _pointer >= other._pointer;}

	friend vector_iterator<T> operator+(difference_type n, const vector_iterator& rhs) {return n + rhs._pointer;} //n + a
	vector_iterator<T> operator+(difference_type n) const {return _pointer + n;} //a + n
	vector_iterator<T> operator-(difference_type n) const {return _pointer - n;} //a - n
	difference_type operator-(const vector_iterator& rhs) const {return _pointer - rhs._pointer;} //a - b
	vector_iterator<T> & operator+=(difference_type n) {_pointer += n; return *this;}
	vector_iterator<T> & operator-=(difference_type n) {_pointer -= n; return *this;}

	friend std::ostream & operator<<(std::ostream & o, vector_iterator<T> & rhs) {o << *rhs._pointer; return o;}
};

template<typename it1, typename it2>
bool operator==(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() == b.get_ptr();}
template<typename it1, typename it2>
bool operator!=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() != b.get_ptr();}
template<typename it1, typename it2>
bool operator<(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() < b.get_ptr();}
template<typename it1, typename it2>
bool operator<=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() <= b.get_ptr();}
template<typename it1, typename it2>
bool operator>(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() > b.get_ptr();}
template<typename it1, typename it2>
bool operator>=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() >= b.get_ptr();}

}

#endif
