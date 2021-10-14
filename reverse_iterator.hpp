#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "utils.hpp"

namespace ft {

template<typename Iterator>
class reverse_iterator {
public:
/*	typedef T value_type;
	typedef std::forward_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef value_type& reference;
*/

	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
	typedef typename iterator_traits<Iterator>::reference           reference;
	typedef typename iterator_traits<Iterator>::pointer             pointer;
	typedef typename iterator_traits<Iterator>::difference_type     difference_type;
	typedef typename iterator_traits<Iterator>::value_type          value_type;

	reverse_iterator() : _pointer(NULL) {}
	reverse_iterator(value_type * ptr) : _pointer(ptr) {}
	reverse_iterator(reverse_iterator const & src) : _pointer(src._pointer) {}
	~reverse_iterator() {}
	reverse_iterator & operator=(reverse_iterator const & rhs) {_pointer = rhs._pointer; return *this;}
	iterator_type base(void) const {return _pointer;}
	operator reverse_iterator<vector_iterator<value_type const> >() const {return reverse_iterator<vector_iterator<value_type const> >(_pointer);} //hummmmmmmmm
	operator reverse_iterator<vector_iterator<value_type> >() {return reverse_iterator<vector_iterator<value_type> >(_pointer);} //hummmmmmmmm

protected:
	iterator_type _pointer;

public:
	reverse_iterator& operator++() {
		_pointer--;
		return *this;
	}

	reverse_iterator operator++(int) {
		reverse_iterator it = *this;
		--(*this);
		return it;
	}

	reverse_iterator& operator--() {
		_pointer++;
		return *this;
	}

	reverse_iterator operator--(int) {
		reverse_iterator it = *this;
		++(*this);
		return it;
	}

	value_type& operator[](int index) {return *(_pointer - index - 1);}
	value_type* operator->() {return _pointer;}
	value_type& operator*() {return *_pointer;}

	bool operator==(const reverse_iterator& other) const {return _pointer == other._pointer;}
	bool operator!=(const reverse_iterator& other) const {return _pointer != other._pointer;}
	bool operator<(const reverse_iterator& other) const {return _pointer > other._pointer;}
	bool operator<=(const reverse_iterator& other) const {return _pointer >= other._pointer;}
	bool operator>(const reverse_iterator& other) const {return _pointer < other._pointer;}
	bool operator>=(const reverse_iterator& other) const {return _pointer <= other._pointer;}

	friend reverse_iterator<Iterator> operator+(difference_type n, const reverse_iterator& rhs) {return n + rhs._pointer;} //n + a
	reverse_iterator<Iterator> operator+(difference_type n) const {return _pointer - n;} //a + n
	reverse_iterator<Iterator> operator-(difference_type n) const {return _pointer + n;} //a - n
	difference_type operator-(const reverse_iterator& rhs) const {return _pointer - rhs._pointer;} //a - b
	reverse_iterator<Iterator> & operator+=(difference_type n) {_pointer -= n; return *this;}
	reverse_iterator<Iterator> & operator-=(difference_type n) {_pointer += n; return *this;}

	friend std::ostream & operator<<(std::ostream & o, reverse_iterator<Iterator> & rhs) {o << *rhs._pointer; return o;}
};

template<typename it1, typename it2>
bool operator==(const reverse_iterator<it1>& a, const reverse_iterator<it2>& b) {return a.base() == b.base();}
template<typename it1, typename it2>
bool operator!=(const reverse_iterator<it1>& a, const reverse_iterator<it2>& b) {return a.base() != b.base();}
template<typename it1, typename it2>
bool operator<(const reverse_iterator<it1>& a, const reverse_iterator<it2>& b) {return a.base() > b.base();}
template<typename it1, typename it2>
bool operator<=(const reverse_iterator<it1>& a, const reverse_iterator<it2>& b) {return a.base() >= b.base();}
template<typename it1, typename it2>
bool operator>(const reverse_iterator<it1>& a, const reverse_iterator<it2>& b) {return a.base() < b.base();}
template<typename it1, typename it2>
bool operator>=(const reverse_iterator<it1>& a, const reverse_iterator<it2>& b) {return a.base() <= b.base();}

}

#endif
