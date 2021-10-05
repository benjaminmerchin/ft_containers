#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

#include <memory>
#include <iostream>
#include <string>

namespace ft {

template<typename T>
class RandomAccessIterator {
public:
	typedef std::forward_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;

	RandomAccessIterator() : _pointer(NULL) {}
	RandomAccessIterator(value_type * ptr) : _pointer(ptr) {}
	RandomAccessIterator(RandomAccessIterator const & src) : _pointer(src._pointer) {}
	~RandomAccessIterator() {}
	RandomAccessIterator & operator=(RandomAccessIterator const & rhs) {_pointer = rhs._pointer; return *this;}

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

	bool operator==(const RandomAccessIterator& other) const {return _pointer == other._pointer;}
	bool operator!=(const RandomAccessIterator& other) const {return _pointer != other._pointer;}
	bool operator<(const RandomAccessIterator& other) const {return _pointer < other._pointer;}
	bool operator<=(const RandomAccessIterator& other) const {return _pointer <= other._pointer;}
	bool operator>(const RandomAccessIterator& other) const {return _pointer > other._pointer;}
	bool operator>=(const RandomAccessIterator& other) const {return _pointer >= other._pointer;}

	friend RandomAccessIterator<T> operator+(difference_type n, const RandomAccessIterator& rhs) {return n + rhs._pointer;} //n + a
	RandomAccessIterator<T> operator+(difference_type n) const {return _pointer + n;} //a + n
	RandomAccessIterator<T> operator-(difference_type n) const {return _pointer - n;} //a - n
	difference_type operator-(const RandomAccessIterator& rhs) const {return _pointer + rhs._pointer;} //a - b
	RandomAccessIterator<T> & operator+=(difference_type n) {_pointer += n; return *this;}
	RandomAccessIterator<T> & operator-=(difference_type n) {_pointer -= n; return *this;}

	friend std::ostream & operator<<(std::ostream & o, RandomAccessIterator<T> & rhs) {o << *rhs;return o;}
};


}

#endif
