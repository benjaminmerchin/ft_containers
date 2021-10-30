#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "map.hpp"

namespace ft {

template<typename T, typename node_type>
class map_iterator {

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef ptrdiff_t difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;

protected:
	node_type _node;

public:
	map_iterator() : _node(NULL) {}
	map_iterator(map_iterator const & src) : _node(src._node) {}
	map_iterator(node_type ptr) : _node(ptr) {}
	map_iterator & operator=(map_iterator const & rhs) {_node = rhs._node; return *this;}
	~map_iterator() {}

	map_iterator& operator++ (void) {increase(); return *this;}
	map_iterator operator++ (int) {map_iterator it = *this; ++(*this); return *this;}
	map_iterator& operator-- (void) {decrease(); return *this;}
	map_iterator operator-- (int) {map_iterator it = *this; --(*this); return *this;}

	node_type get_node() {return _node;}
	reference operator*() const {return _node->value;}
	pointer operator->() const {return &(operator*());}
	operator map_iterator<const T, node_type>() const {return map_iterator<const T, node_type>(_node);}

	//template<typename U>
	bool operator==(const map_iterator<T, node_type> other) {return _node == other._node;}
	//template<typename U>
	bool operator!=(const map_iterator<T, node_type> other) {return _node != other._node;}

private:
	void increase() {
		if (_node->right) {
			_node = _node->right;
			while (_node->left)
				_node = _node->left;
		}
		else {
			node_type temp = _node;
			_node = _node->parent;
			while (_node->left != temp) {
				temp = _node;
				_node = _node->parent;
			}
		}
	}

	void decrease() {
		if (_node->left) {
			_node = _node->left;
			while (_node->right)
				_node = _node->right;
		}
		else {
			node_type temp = _node;
			_node = _node->parent;
			while (_node->right != temp) {
				temp = _node;
				_node = _node->parent;
			}
		}
	}

};


}

#endif
