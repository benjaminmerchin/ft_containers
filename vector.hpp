#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

//reuse the functions from the allocator_traits: allocate, deallocate, construct, destroy & max_size
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
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef vector_iterator<value_type>              iterator;
	typedef vector_iterator<value_type const>        const_iterator;
	typedef ft::reverse_iterator<iterator>           reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

protected:
	allocator_type _alloc_type;
	pointer_type _array;
	size_type _size;
	size_type _capacity;

public:
//MEMBER FUNCTIONS
	// 4 constructors required: default/fill/range/copy
	// default (1)
	explicit vector (const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _array(NULL), _size(0), _capacity(0) {}
	// fill (2)
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _array(NULL), _size(n), _capacity(n) {
		_array = _alloc_type.allocate(n);
		for (size_type i = 0; i < n; i++)
			_alloc_type.construct(&_array[i], val);
	}
	// range (3)
	template <class InputIterator>
	vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _array(NULL), _size(0), _capacity(0) {
		size_type n = 0;
		size_type i = 0;
		for (InputIterator it = first; it != last; it++)
			n++;
		reserve(n);
		for (InputIterator it = first; it != last; it++, i++)
			_alloc_type.construct(&_array[i], *it);
		_size = n;
	}
	// copy (4)
	vector (const vector& x) : _alloc_type(x._alloc_type), _array(NULL), _size(x._size), _capacity(x._capacity) {
		_array = _alloc_type.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
			_alloc_type.construct(&_array[i], x._array[i]);
	}
	vector& operator= (const vector& x) {
		if (_size < x._size) {
			reserve(x._size);
			resize(x._size);
		}
		else
			for (size_type i = 0; i < _size; i++)
				_alloc_type.destroy(&_array[i]);
		_size = x._size;
		for (size_type i = 0; i < _size; i++)
			_alloc_type.construct(&_array[i], x._array[i]);
		return *this;
	}
	~vector() {
		for (size_type i = 0; i < _size; i++)
			_alloc_type.destroy(&_array[i]);
		_alloc_type.deallocate(_array, _capacity);
	}

//ITERATORS
// begin Return iterator to beginning (public member function )
	iterator begin() {return iterator(_array);}
	const_iterator begin() const {return const_iterator(_array);}
// end Return iterator to end (public member function )
	iterator end() {return iterator(_array + _size);}
	const_iterator end() const {return const_iterator(_array + _size);}
// rbegin Return reverse iterator to reverse beginning (public member function )
	reverse_iterator rbegin() {return reverse_iterator(end());}
	const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
// rend Return reverse iterator to reverse end (public member function )
	reverse_iterator rend() {return reverse_iterator(begin());}
	const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

//CAPACITY
	size_type size() const {return _size;}
	size_type max_size() const {return _alloc_type.max_size();}
	size_type capacity() const {return _capacity;}
	bool empty() const {return _size == 0 ? true : false;}
	void reserve(size_type n) {
		if (n > _capacity) {
			pointer_type update = _alloc_type.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_alloc_type.construct(&update[i], _array[i]);
				_alloc_type.destroy(&_array[i]);
			}
			_alloc_type.deallocate(_array, _capacity = n);
			_array = update;
			_capacity = n;
		}
	}
	void resize(size_type n, value_type val = value_type()) {
		if (n > _capacity) {
			if (n < _capacity * 2)
				reserve(_capacity * 2);
			else
				reserve(n);
		}
		for (size_type i = _size; i < n; i++)
			_alloc_type.construct(&_array[i], val);
		for (size_type i = n; i < _size; i++)
			_alloc_type.destroy(&_array[i]);
		_size = n;
	}

//ELEMENT ACCESS
	reference operator[] (size_type n) {return _array[n];}
	const_reference operator[] (size_type n) const {return _array[n];}
	reference at (size_type n) {
		if (n >= _size)
			throw std::out_of_range("out of range");
		return _array[n];
	}
	const_reference at (size_type n) const {
		if (n >= _size)
			throw std::out_of_range("out of range");
		return _array[n];
	}
	reference front() {return _array[0];}
	const_reference front() const {return _array[0];}
	reference back() {return _array[_size - 1];}
	const_reference back() const {return _array[_size - 1];}

//MODIFIERS
	template <class InputIterator>
	void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
		size_type n = 0;
		size_type i = 0;
		for (InputIterator it = first; it != last; it++)
			n++;
		reserve(n);
		resize(n);
		for (size_type i = 0; i < n && i < _size; i++)
			_alloc_type.destroy(&_array[i]);
		for (InputIterator it = first; it != last; it++, i++)
			_alloc_type.construct(&_array[i], *it);
		if (n > _size)
			_size = n;
	}
	void assign (size_type n, const value_type& val) {
		reserve(n);
		resize(n);
		for (size_type i = 0; i < n && i < _size; i++)
			_alloc_type.destroy(&_array[i]);
		for (size_type i = 0; i < n; i++)
			_alloc_type.construct(&_array[i], val);
		if (n > _size)
			_size = n;
	}
	void push_back(const value_type& val) {
		if (_size == _capacity) {
			if (_capacity == 0)
				reserve(1);
			else
				reserve(_capacity * 2);
		}
		_alloc_type.construct(&_array[_size], val);
		_size++;
	}
	void pop_back() {_alloc_type.destroy(&_array[--_size]);}
	iterator insert (iterator position, const value_type& val) {
		difference_type diff = position.get_ptr() - _array;
		insert(position, 1, val);
		return iterator(begin() + diff);
	}
	void insert (iterator position, size_type n, const value_type& val) {
		size_type begin_to_pos = 0;
		size_type pos_to_end = 0;
		iterator it = begin();
		for (; it != position; it++)
			begin_to_pos++;
		for (; it != end(); it++)
			pos_to_end++;
		if (_size + n > _capacity) {
			if (_size + n < _capacity * 2)
				reserve(_capacity * 2);
			else
				reserve(_size + n);
		}
		for (size_type i = 0; i < pos_to_end; i++) {
			_alloc_type.construct(&_array[begin_to_pos + n + pos_to_end - i - 1], _array[begin_to_pos + pos_to_end - i - 1]);
			_alloc_type.destroy(&_array[begin_to_pos + pos_to_end - i - 1]);
		}
		for (size_type i = 0; i < n; i++) {
			_alloc_type.construct(&_array[begin_to_pos + i], val);
		}
		_size += n;
	}
	template <class InputIterator>
	void insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
		size_type n = 0;
		size_type begin_to_pos = 0;
		size_type pos_to_end = 0;
		for (InputIterator it = first; it != last; it++)
			n++;
		iterator it = begin();
		for (; it != position; it++)
			begin_to_pos++;
		for (;it != end(); it++)
			pos_to_end++;
		if (_size + n > _capacity) {
			if (_size + n < _capacity * 2)
				reserve(_capacity * 2);
			else
				reserve(_size + n);
		}
		for (size_type i = 0; i < pos_to_end; i++) {
			_alloc_type.construct(&_array[begin_to_pos + n + pos_to_end - i - 1], _array[begin_to_pos + pos_to_end - i - 1]);
			_alloc_type.destroy(&_array[begin_to_pos + pos_to_end - i - 1]);
		}
		InputIterator curs = first;
		for (size_type i = 0; i < n; i++) {
			_alloc_type.construct(&_array[begin_to_pos + i], *curs);
			curs++;
		}
		_size += n;
	}
	iterator erase(iterator position) {return erase(position, position + 1);}
	iterator erase(iterator first, iterator last) {
		size_type begin_to_first = 0;
		size_type first_to_last = 0;
		size_type last_to_end = 0;
		for (iterator it = begin(); it != first; it++)
			begin_to_first++;
		for (iterator it = first; it != last; it++)
			first_to_last++;
		for (iterator it = last; it != end(); it++)
			last_to_end++;
		for (size_type i = 0; i < last_to_end; i++) {
			_alloc_type.destroy(&_array[begin_to_first + i]);
			_alloc_type.construct(&_array[begin_to_first + i], _array[begin_to_first + i + first_to_last]);
		}
		for (size_type i = 0; i < first_to_last; i++)
			_alloc_type.destroy(&_array[begin_to_first + last_to_end + i]);
		_size -= first_to_last;
		return first;
	}
	void swap(vector& x) {
		allocator_type temp_alloc_type = x._alloc_type;
		pointer_type temp_array = x._array;
		size_type temp_size = x._size;
		size_type temp_capacity = x._capacity;
		x._alloc_type = _alloc_type;
		x._array = _array;
		x._size = _size;
		x._capacity = _capacity;
		_alloc_type = temp_alloc_type;
		_array = temp_array;
		_size = temp_size;
		_capacity = temp_capacity;
	}
	void clear() {_size = 0;}

//ALLOCATOR
	allocator_type get_allocator() const {return _alloc_type;}

};

//NON-MEMBER FUNCTION OVERLOADS
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(lhs == rhs);}
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (lhs < rhs || lhs == rhs);}
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return rhs < lhs;}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (lhs > rhs || lhs == rhs);}
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {x.swap(y);}

}

#endif
