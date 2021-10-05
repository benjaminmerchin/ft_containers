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
	typedef std::forward_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
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

	bool operator==(const vector_iterator& other) const {return rai::operator==(other);}
	bool operator!=(const vector_iterator& other) const {return rai::operator!=(other);}

	friend vector_iterator<T> operator+(difference_type n, const vector_iterator<T>& rhs) {return rai::operator+(n, rhs);} //n + a
	vector_iterator<T> operator+(difference_type n) const {return rai::operator+(n);} //a + n
	vector_iterator<T> operator-(difference_type n) const {return rai::operator-(n);} //a - n
	difference_type operator-(const vector_iterator<T>& rhs) const {return rai::operator-(rhs);} //a - b
	vector_iterator<T> & operator-=(difference_type n) {rai::operator-=(n); return *this;}
	vector_iterator<T> & operator+=(difference_type n) {rai::operator+=(n); return *this;}

	friend std::ostream & operator<<(std::ostream & o, vector_iterator<T> & rhs) {return rai::operator<<(o, rhs);}
};

template<typename T>
class const_vector_iterator : public ft::RandomAccessIterator<T> {
public:
	typedef T value_type;
	typedef std::forward_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer_type;
	typedef value_type& reference_type;
	typedef RandomAccessIterator<T> rai;

	const_vector_iterator() : rai(NULL) {}
	const_vector_iterator(value_type * ptr) : rai(ptr) {}
	const_vector_iterator(const_vector_iterator const & src) : rai(src) {}
	~const_vector_iterator() {}
	const_vector_iterator & operator=(const_vector_iterator const & rhs) {rai::_pointer = rhs._pointer;return *this;}

	const_vector_iterator& operator++() { rai::operator++(); return *this; }
	const_vector_iterator operator++(int) { return rai::operator++(0); }
	const_vector_iterator& operator--() { rai::operator--(); return *this; }
	const_vector_iterator operator--(int) { return rai::operator--(0); }

	value_type& operator[](int index) const {return *(rai::_pointer + index);}
	value_type* operator->() const {return rai::_pointer;}
	value_type& operator*() const {return *rai::_pointer;}

	bool operator==(const const_vector_iterator& other) const {return rai::operator==(other);}
	bool operator!=(const const_vector_iterator& other) const {return rai::operator!=(other);}

	friend const_vector_iterator<T> operator+(difference_type n, const const_vector_iterator<T>& rhs) {return rai::operator+(n, rhs);} //n + a
	const_vector_iterator<T> operator+(difference_type n) const {return rai::operator+(n);} //a + n
	const_vector_iterator<T> operator-(difference_type n) const {return rai::operator-(n);} //a - n
	difference_type operator-(const const_vector_iterator<T>& rhs) const {return rai::operator-(rhs);} //a - b
	const_vector_iterator<T> & operator-=(difference_type n) {rai::operator-=(n); return *this;}
	const_vector_iterator<T> & operator+=(difference_type n) {rai::operator+=(n); return *this;}

	friend std::ostream & operator<<(std::ostream & o, const_vector_iterator<T> & rhs) {return rai::operator<<(o, rhs);}
};

}

#endif
