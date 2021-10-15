#ifndef REVERSE_IT_HPP
#define REVERSE_IT_HPP

#include <memory>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "vector_iterator.hpp"

namespace ft {

template<typename Iterator>
class reverse_it {
public:
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
	typedef typename iterator_traits<Iterator>::reference           reference;
	typedef typename iterator_traits<Iterator>::pointer             pointer;
	typedef typename iterator_traits<Iterator>::difference_type     difference_type;
	typedef typename iterator_traits<Iterator>::value_type          value_type;

	reverse_it() : _pointer(NULL) {}
	reverse_it(iterator_type ptr) : _pointer(ptr) {}
	reverse_it(reverse_it const & src) : _pointer(src._pointer) {}
	~reverse_it() {}
	reverse_it & operator=(reverse_it const & rhs) {_pointer = rhs._pointer; return *this;}
	iterator_type base(void) const {return _pointer;}
	operator reverse_it<vector_iterator<value_type const> >() const {return reverse_it<vector_iterator<value_type const> >(_pointer);}
	operator reverse_it<vector_iterator<value_type> >() {return reverse_it<vector_iterator<value_type> >(_pointer);}

protected:
	iterator_type _pointer;

public:
	reverse_it& operator++() {
		_pointer--;
		return *this;
	}

	reverse_it operator++(int) {
		reverse_it it = *this;
		--(*this);
		return it;
	}

	reverse_it& operator--() {
		_pointer++;
		return *this;
	}

	reverse_it operator--(int) {
		reverse_it it = *this;
		++(*this);
		return it;
	}

	value_type& operator[](int index) {return *(_pointer - index - 1);}
	value_type* operator->() {return _pointer;}
	value_type& operator*() {return *_pointer;}

	bool operator==(const reverse_it& other) const {return _pointer == other._pointer;}
	bool operator!=(const reverse_it& other) const {return _pointer != other._pointer;}
	bool operator<(const reverse_it& other) const {return _pointer > other._pointer;}
	bool operator<=(const reverse_it& other) const {return _pointer >= other._pointer;}
	bool operator>(const reverse_it& other) const {return _pointer < other._pointer;}
	bool operator>=(const reverse_it& other) const {return _pointer <= other._pointer;}

	friend reverse_it<Iterator> operator+(difference_type n, const reverse_it& rhs) {return n + rhs._pointer;} //n + a
	reverse_it<Iterator> operator+(difference_type n) const {return _pointer - n;} //a + n
	reverse_it<Iterator> operator-(difference_type n) const {return _pointer + n;} //a - n
	difference_type operator-(const reverse_it& rhs) const {return _pointer - rhs._pointer;} //a - b
	reverse_it<Iterator> & operator+=(difference_type n) {_pointer -= n; return *this;}
	reverse_it<Iterator> & operator-=(difference_type n) {_pointer += n; return *this;}

	friend std::ostream & operator<<(std::ostream & o, reverse_it<Iterator> & rhs) {o << *rhs._pointer; return o;}
};

template<typename it1, typename it2>
bool operator==(const reverse_it<it1>& a, const reverse_it<it2>& b) {return a.base() == b.base();}
template<typename it1, typename it2>
bool operator!=(const reverse_it<it1>& a, const reverse_it<it2>& b) {return a.base() != b.base();}
template<typename it1, typename it2>
bool operator<(const reverse_it<it1>& a, const reverse_it<it2>& b) {return a.base() > b.base();}
template<typename it1, typename it2>
bool operator<=(const reverse_it<it1>& a, const reverse_it<it2>& b) {return a.base() >= b.base();}
template<typename it1, typename it2>
bool operator>(const reverse_it<it1>& a, const reverse_it<it2>& b) {return a.base() < b.base();}
template<typename it1, typename it2>
bool operator>=(const reverse_it<it1>& a, const reverse_it<it2>& b) {return a.base() <= b.base();}

}

#endif
