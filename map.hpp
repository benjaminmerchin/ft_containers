#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <string>
#include "pair.hpp"
#include "tree.hpp"
#include "map_iterator.hpp"
#include "vector.hpp"
#include "utils.hpp"

#define DEBUG 1

namespace ft {

template <typename value_type>
struct node {
	value_type value;
	node *left;
	node *right;
	node *parent;
	int height;
	bool last;
	node(value_type v, node *l, node *r, node *p, bool e = false) : value(v), left(l), right(r), parent(p), height(1), last(e) {}
	~node() {}
};

//Association of key and value_type https://cplusplus.com/reference/map/map/
//Tree Tutorial used: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
template < class Key,                                           // map::key_type
           class T,                                             // map::mapped_type
           class Compare = std::less<Key>,                      // map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> > // map::allocator_type
           >
class map {

public:
	typedef Key                                                   key_type;
	typedef T                                                     mapped_type;
	typedef ft::pair<const key_type,mapped_type>                  value_type;
	typedef Compare                                               key_compare;
	typedef node<value_type>                                      node_type;
	class value_compare {
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const {return comp(x.first, y.first);}
	};
	typedef Alloc                                                 allocator_type;
	typedef typename allocator_type::template rebind<node_type>::other node_allocator;
	typedef typename allocator_type::reference                    reference;
	typedef typename allocator_type::const_reference              const_reference;
	typedef typename allocator_type::pointer                      pointer;
	typedef typename allocator_type::const_pointer                const_pointer;
	typedef typename allocator_type::size_type                    size_type;
	typedef typename allocator_type::difference_type              difference_type;
	typedef map_iterator<value_type, node_type*>                  iterator;
	typedef map_iterator<const value_type, node_type*>            const_iterator;
	typedef ft::reverse_iterator<iterator>                        reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>                  const_reverse_iterator;
/*
	iterator	a bidirectional iterator to value_type	convertible to const_iterator
	const_iterator	a bidirectional iterator to const value_type	
	reverse_iterator	reverse_iterator<iterator>	
	const_reverse_iterator	reverse_iterator<const_iterator>
*/

// 	template <class Type> struct rebind {
//   typedef allocator<Type> other;
// };

protected:
	node_allocator _alloc_type;
	key_compare _key_compare;
	size_type _size;
	node_type *_root;

public:
//CONSTRUCTORS
	//empty (1)
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _key_compare(comp), _size(0), _root(NULL) {}
	//range (2)
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _key_compare(comp), _size(0), _root(NULL) {
		(void)first;
		(void)last;
	}
	//copy (3)
	map (const map& x) : _alloc_type(x._alloc_type), _key_compare(x._key_compare), _size(0), _root(NULL) {}
	~map () {clear_from_node(_root);}
	map& operator= (const map& x) {
		(void)x;
	}

//ITERATORS
	iterator begin() {
		if (_size == 0)
			return iterator(_root); //pb ?
		node_type * temp = _root;
		while (temp && temp->left)
			temp = temp->left;
		return iterator(temp);
		//return (iterator(_root));
	}
//	const_iterator begin() const {}
	iterator end() {
		if (_size == 0)
			return iterator(_root);
		node_type * temp = _root;
		while(temp && temp->right)
			temp = temp->right;
		return iterator(temp);
		// while (!)
	}
// const_iterator end() const;
// reverse_iterator rbegin();
// const_reverse_iterator rbegin() const;
// reverse_iterator rend();
// const_reverse_iterator rend() const;

//CAPACITY
	bool empty() const {return (_size == 0 ? true : false);}
	size_type size() const {return _size;}
	size_type max_size() const {return _alloc_type.max_size();}

//ELEMENT ACCESS
// mapped_type& operator[] (const key_type& k);

//MODIFIERS
// insert

pair<iterator,bool> insert (const value_type& val) { //value_type : pair<const key_type,mapped_type> 
	node_type *temp = _root;
	(void)val;
	(void)temp;
	if (DEBUG) std::cerr << "insert:   " << val.first << ' ' << val.second << std::endl;
	_root = insert_node_check_root(val, _root);
	
	return pair<iterator,bool>(NULL, true);
}
// erase
size_type erase (const key_type& k) {
	size_type backup = _size;
	_root = delete_node(_root, k);
	return backup - _size;
}
// swap
	void clear() {
		clear_from_node(_root);
	}

//OBSERVERS
	key_compare key_comp() const {return _key_compare;}
	value_compare value_comp() const {return (value_compare(this->_key_compare));}

//OPERATIONS
// iterator find (const key_type& k);
// const_iterator find (const key_type& k) const;
// size_type count (const key_type& k) const;
// iterator lower_bound (const key_type& k);
// const_iterator lower_bound (const key_type& k) const;
// iterator upper_bound (const key_type& k);
// const_iterator upper_bound (const key_type& k) const;
// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
// pair<iterator,iterator>             equal_range (const key_type& k);

//ALLOCATORS
	allocator_type get_allocator() const {return _alloc_type;}

//TREE
	void print_all() {
		print(_root);
	}

private:

	void print(node_type *start, std::string path = "") {
		/*if (start && start->last)
			return;*/
		if (start) {
			print(start->left, path + "L");
			std::cout << path << ' ' << start->value.first << '_' << start->value.second;
			if (start->parent)
				std::cout << " p:" << start->parent->value.first << ' ';
			else
				std::cout << " root";
			std::cout << " last:" << start->last;
			std::cout << std::endl;
			print(start->right, path + "R");
		}
	}

	node_type* new_node(const value_type& val, node_type *parent) {
		node_type *temp = _alloc_type.allocate(1);
		_alloc_type.construct(temp, node_type(val, NULL, NULL, parent, false));
		/*
		std::cerr << temp->last << "-KKKOKOKKO\n";
		temp->last = true;
		temp->parent = parent;
		temp->right = NULL;
		temp->left = NULL;
		temp->height = 1;
		temp->end = false;
		*/
		if (DEBUG) std::cerr << "new_node: " << temp->value.first << ' ' << temp->value.second << std::endl;
		//node<value_type> 
	/*
		temp->value = pair<int,int>(1, 2);
		temp->value.first = val.first;
		temp->value.second = val.second;
		(void)val;
		(void)parent;
		(void)temp;
	*/
		_size++;
		return temp;
	}

	int max(int a, int b) {return (a > b)? a : b;}

	int height(node_type *node) {
		if (!node)
			return 0;
		return node->height;
	}

	int get_balance(node_type *node) {
		if (!node)
			return 0;
		return height(node->left) - height(node->right);
	}

	node_type* min_value_node(node_type *node) {
		node_type *current = node;
		while (current->left != NULL)
			current = current->left;
		return current;
	}

	node_type* max_value_node(node_type *node) {
		node_type *current = node;
		while (current->right != NULL)
			current = current->right;
		return current;
	}

	node_type* insert_node_check_root(const value_type& val, node_type *current, node_type *parent = NULL) {
		if (!_root) {
			if(DEBUG) cerr<<"                      GENERATING LAST\n";
			_root = new_node(val, NULL);
			node_type *last = new_node(val, _root); //dummy value in the last node
			_root->right = last;
			last->last = true;
			_size++;
			std::cerr << _root->last << ' ' << _root->right->last << std::endl;
			return _root;
		}
		if (_root->last) {
			node_type *new_root = new_node(val, NULL);
			_root->parent = new_root;
			new_root->right = _root;
			_root = new_root;
			_size++;
			return _root;
		}
		return insert_node(val, current, parent);
	}

	node_type* insert_node(const value_type& val, node_type *current, node_type *parent) {
		if (!current)
			return new_node(val, parent);
		if (current->last) {
			node_type *to_insert = new_node(val, NULL);
			current->parent = to_insert;
			to_insert->right = current;
			current = to_insert;
			_size++;
			return current;
		}
		if (_key_compare(val.first, current->value.first))
			current->left = insert_node(val, current->left, current);
		else if (_key_compare(current->value.first, val.first))
			current->right = insert_node(val, current->right, current);
		else
			return current;

		current->height = 1 + max(height(current->left), height(current->right));
		//rotate here if neccessary
/*
		// Left Left Case
		if (balance > 1 && getBalance(root->left) >= 0)
			return rightRotate(root);

		// Left Right Case
		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// Right Right Case
		if (balance < -1 && getBalance(root->right) <= 0)
			return leftRotate(root);

		// Right Left Case
		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
*/

		return current;
	}

	node_type* delete_node(node_type *current, const key_type& key) {
		if (!current)
			return current;
		if (_key_compare(key, current->value.first))
			current->left = delete_node(current->left, key);
		else if (_key_compare(current->value.first, key))
			current->right = delete_node(current->right, key);
		else { //we found the node
			//deleting process here
			if (!current->left || !current->right) {
				node_type *temp = current->left ? current->left : current->right;
				if (!current->left && !current->right) {
					temp = current;
					if (DEBUG) std::cerr << "del_node: " << temp->value.first << ' ' << temp->value.second << std::endl;
					_alloc_type.destroy(temp);
					_alloc_type.deallocate(temp, 1);
					current = NULL;
					_size--;
				}
				else {
					temp->parent = current->parent;
					node_type *temp2 = current;
					current = temp;
					if (DEBUG) std::cerr << "del_node: " << temp2->value.first << ' ' << temp2->value.second << std::endl;
					_alloc_type.destroy(temp2);
					_alloc_type.deallocate(temp2, 1);
					_size--;
				}
			}
			else {
				node_type *temp = min_value_node(current->right);
				if (temp != current->right) {
					temp->right = current->right;
					current->right->parent = temp;
				}
				temp->left = current->left;
				current->left->parent = temp;
				temp->parent->left = NULL;
				temp->parent = current->parent;
				if (_root == current)
					_root = temp; //doute ici
				if (DEBUG) std::cerr << "del_node: " << current->value.first << ' ' << current->value.second << std::endl;
				_alloc_type.destroy(current);
				_alloc_type.deallocate(current, 1);
				/*
				node_type *temp = min_value_node(current->right);
				current->value = temp->value;
				current->right = delete_node(current->right, key);
				*/
				//std::cerr << "problem 2 child\n";
				current = temp;
			}
		}

		if (!current)
			return current;
		current->height = 1 + max(height(current->left), height(current->right));
		//rotate here if necessary
		return current;
	}

	void clear_from_node(node_type *current) {
		if (current) {
			clear_from_node(current->left);
			clear_from_node(current->right);
			_alloc_type.destroy(current);
			_alloc_type.deallocate(current, 1);
			_size--;
			if (current == _root)
				_root = NULL;
		}
	}

};

}

#endif

/*

node<pair<const int, int> > *
ft::pair<const int, int> *

*/