#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "map.hpp"

namespace ft {

template<typename T, typename node_pointer>
class map_iterator {

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;

protected:
	node_pointer _node;

public:
	map_iterator() : _node(NULL) {}
	map_iterator(node_pointer ptr) : _node(ptr) {}
	map_iterator(map_iterator const & src) : _node(src._node) {}
	map_iterator & operator=(map_iterator const & rhs) {_node = rhs._node; return *this;}
	~map_iterator() {}

	map_iterator& operator++ (void) {increase(); return *this;}
	map_iterator operator++ (int) {map_iterator it = *this; ++(*this); return it;}
	map_iterator& operator-- (void) {decrease(); return *this;}
	map_iterator operator-- (int) {map_iterator it = *this; --(*this); return it;}

	reference operator*() const {return _node->value;}
	pointer operator->() const {return &(operator*());}
	node_pointer get_node() {return _node;}
	node_pointer get_node() const {return _node;}
	operator map_iterator<const T, node_pointer>() const {return map_iterator<const T, node_pointer>(_node);}

private:
	void increase() {
		if (_node->right) {
			_node = _node->right;
			while (_node->left)
				_node = _node->left;
		}
		else {
			node_pointer temp = _node;
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
			node_pointer temp = _node;
			_node = _node->parent;
			while (_node->right != temp) {
				temp = _node;
				_node = _node->parent;
			}
		}
	}

	template<typename it1, typename it2>
	friend bool operator==(const map_iterator<it1, node_pointer>& a, const map_iterator<it2, node_pointer>& b) {return a.get_node() == b.get_node();}
	template<typename it1, typename it2>
	friend bool operator!=(const map_iterator<it1, node_pointer>& a, const map_iterator<it2, node_pointer>& b) {return a.get_node() != b.get_node();}
	template<typename it1, typename it2>
	friend bool operator<(const map_iterator<it1, node_pointer>& a, const map_iterator<it2, node_pointer>& b) {return a.get_node() < b.get_node();}
	template<typename it1, typename it2>
	friend bool operator<=(const map_iterator<it1, node_pointer>& a, const map_iterator<it2, node_pointer>& b) {return a.get_node() <= b.get_node();}
	template<typename it1, typename it2>
	friend bool operator>(const map_iterator<it1, node_pointer>& a, const map_iterator<it2, node_pointer>& b) {return a.get_node() > b.get_node();}
	template<typename it1, typename it2>
	friend bool operator>=(const map_iterator<it1, node_pointer>& a, const map_iterator<it2, node_pointer>& b) {return a.get_node() >= b.get_node();}

};

}

#endif
