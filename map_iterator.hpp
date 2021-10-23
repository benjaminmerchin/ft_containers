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


};

}

#endif
