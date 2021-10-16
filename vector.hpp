#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <string>
#include "vector_iterator.hpp"
#include "reverse_it.hpp"
#include "utils.hpp"

//https://en.cppreference.com/w/cpp/header/vector copier le header class template
//iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.

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
	typedef vector_iterator<value_type>              iterator;
	typedef vector_iterator<value_type const>        const_iterator;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef reverse_it<iterator>                     reverse_iterator;
	typedef reverse_it<const_iterator>               const_reverse_iterator;

protected:
	allocator_type _alloc_type; //ie:        std::allocator<T> _alloc_type; basically we store the Alloc which is a class
	pointer_type _array;
	size_type _size;
	size_type _capacity; //toujours une puissance de 2

public:
//MEMBER FUNCTIONS
	// 4 constructors required: default/fill/range/copy
	// default (1)
	explicit vector (const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _array(NULL), _size(0), _capacity(0) {}
	// fill (2)
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _size(n), _capacity(n) {
		_array = _alloc_type.allocate(n);
		for (size_type i = 0; i < n; i++)
			_array[i] = val;
		//std::cerr << "Fill Allocator\n";
		//std::cerr << val << std::endl;
	}
	// range (3)
	template <class InputIterator>
	vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc_type(alloc) {
		for (InputIterator it = first; it != last; ++it)
			push_back(*it);
		//std::cerr << "Range Allocator\n";
	}
	// copy (4)
	vector (const vector& x) : _alloc_type(x._alloc_type), _size(x._size), _capacity(x._capacity) {
		_array = _alloc_type.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
			_array[i] = x._array[i];
		//std::cerr << "Copy Allocator\n";
	}
	vector& operator= (const vector& x) {
		if (_size < x._size) {
			_alloc_type.deallocate(_array, _capacity);
			_alloc_type.allocate(x._size);
			_capacity = x._size;
		}
		_size = x._size;
		for (size_type i = 0; i < _size; i++)
			_array[i] = x._array[i];
		return *this;
	}
	~vector() {_alloc_type.deallocate(_array, _capacity);}

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
	void reserve(size_type n) {add_space(n - _capacity);}
	void resize(size_type n, value_type val = value_type()) {
		if (n > _size)
			_size = n;
		add_space(n - _capacity);
		for (size_type i = _size; i < n; i++)
			_array[n] = val;
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
		for (InputIterator it = first; it != last; ++it)
			push_back(*it);
	}
	void assign (size_type n, const value_type& val) {
		_array = _alloc_type.allocate(n);
		_size = n;
		for (size_type i = 0; i < n; i++)
			_array[i] = val;
	}
	void push_back(const value_type& val) {
		if (_size == _capacity) //size is always lower (enough space) or equal
			add_space(1);
		_array[_size++] = val;
	}
	void pop_back() {_size--;}
	iterator insert (iterator position, const value_type& val) {
		insert(position, 1, val);
		return position;
	}
	void insert (iterator position, size_type n, const value_type& val) {
		size_type pos = 0;
		size_type until_end = 0;
		iterator it = begin();
		iterator aaa = begin();
		--aaa;
		for (; it != position; ++it)
			pos++;
		for (;it != end(); ++it)
			until_end++;
		if (_size + n > _capacity) { //on doit reallouer
			pointer_type new_array = _alloc_type.allocate(_size + n);
			size_type i = 0;
			for (; i < pos; i++)
				new_array[i] = _array[i];
			for (; i < pos + n; i++)
				new_array[i] = val;
			for (; i < pos + n + until_end; i++)
				new_array[i] = _array[i - n];
			_alloc_type.deallocate(_array, _capacity);
			_array = new_array;
			_size += n;
			_capacity = _size + n;
		}
		else { //pas besoin de reallouer
			for (size_type i = 0; i < until_end; i++)
				_array[_size + n - i] = _array[_size - i];
			//_array[pos + until_end + n - i] = _array[pos + until_end - i]
			for (size_type i = 0; i < n; i++)
				_array[pos + i] = val;
			_size += n;
		}
		//std::cerr << "ici";
	}
	template <class InputIterator>
	void insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
		size_type pos = 0;
		size_type until_end = 0;
		size_type n = 0;
		for (InputIterator it = first; it != last; ++it)
			n++;
		iterator it = begin();
		for (; it != position; ++it)
			pos++;
		for (;it != end(); ++it)
			until_end++;
		if (_size + n > _capacity) { //on doit reallouer
			pointer_type new_array = _alloc_type.allocate(_size + n);
			size_type i = 0;
			for (; i < pos; i++)
				new_array[i] = _array[i];
			for (; i < pos + n; i++, ++first)
				new_array[i] = *first;
			for (; i < pos + n + until_end; i++)
				new_array[i] = _array[i - n];
			_alloc_type.deallocate(_array, _capacity);
			_array = new_array;
			_size += n;
			_capacity = _size + n;
		}
		else { //pas besoin de reallouer
			for (size_type i = 0; i < until_end; i++)
				_array[_size + n - i] = _array[_size - i];
			for (size_type i = 0; i < n; i++, ++first)
				_array[pos + i] = *first;
			_size += n;
		}
	}
	iterator erase(iterator position) {
		for (size_type i = position; i < _size + 1; i++)
			_array[i] = _array[i + 1];
		_size--;
		return position;
	}
	iterator erase(iterator first, iterator last) {
		iterator last_cursor = last;
		iterator end_cursor = end();
		for (; first != last && first != end_cursor; ++first, ++last_cursor, --_size)
			*first = *last_cursor;
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

private:
	void add_space(int n) {
		if (n + _size <= _capacity || n < 0) //no need to add space
			return ;
		size_type capacity_backup = _capacity;
		if (_capacity == 0)
			_capacity = 1;
		while (n + _size > _capacity)
			_capacity *= 2;
		pointer_type update = _alloc_type.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
			update[i] = _array[i];
		_alloc_type.deallocate(_array, capacity_backup);
		_array = update;
	}
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
