#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <string>
#include "pair.hpp"
#include "tree.hpp"
#include "map_iterator.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"

#define DEBUG 0

namespace ft {

template <typename V>
struct node {
	V value;
	node *left;
	node *right;
	node *parent;
//	int height;
	bool last;
	node(V v, node *l, node *r, node *p, bool e = false) : value(v), left(l), right(r), parent(p)/*, height(1)*/, last(e) {}
	~node() {}
};

//Association of key and value_type https://cplusplus.com/reference/map/map/
//Tree Tutorial used: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
template < class Key,                                           // map::key_type
           class T,                                             // map::mapped_type
           class Compare = ft::less<Key>,                      // map::key_compare
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
		friend class map;
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
	map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc_type(alloc), _key_compare(comp), _size(0), _root(NULL) {insert(first, last);}
	//copy (3)
	map (const map& x) : _alloc_type(x._alloc_type), _key_compare(x._key_compare), _size(0), _root(NULL) {*this = x;}
	~map () {clear_from_node(_root);}

	map& operator= (const map& x) {
		if (DEBUG) std::cerr << "BBBBB\n";
		clear_from_node(_root);
		insert(x.begin(), x.end());
		return *this;
	}

//ITERATORS
	iterator begin() {
		if (_size == 0)
			return iterator(_root);
		node_type * temp = _root;
		while (temp && temp->left)
			temp = temp->left;
		return iterator(temp);
	}
	const_iterator begin() const {
		if (_size == 0)
			return const_iterator(_root);
		node_type * temp = _root;
		while (temp && temp->left)
			temp = temp->left;
		return const_iterator(temp);
	}
	iterator end() {
		if (_size == 0)
			return iterator(_root);
		node_type * temp = _root;
		while(temp && !temp->last)
			temp = temp->right;
		return iterator(temp);
	}
	const_iterator end() const {
		if (_size == 0)
			return const_iterator(_root);
		node_type * temp = _root;
		while(temp && !temp->last)
			temp = temp->right;
		return const_iterator(temp);
	}
	reverse_iterator rbegin() {return reverse_iterator(end()--);}
	const_reverse_iterator rbegin() const {return const_reverse_iterator(end()--);}
	reverse_iterator rend() {return reverse_iterator(begin());}
	const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

//CAPACITY
	bool empty() const {return _size == 0;}
	size_type size() const {return _size;}
	size_type max_size() const {return _alloc_type.max_size();}

//ELEMENT ACCESS
	mapped_type& operator[] (const key_type& k) {
		if (DEBUG) std::cerr << k << ' ' << mapped_type() << " operator[]\n";
		node_type *temp = position_of_a_key(k);
		if (temp)
			return temp->value.second;
		insert(value_type(k,mapped_type()));
		return position_of_a_key(k)->value.second;
		/*
		return insert(value_type(k,mapped_type())).first->second;
		*/
	}

//MODIFIERS
	pair<iterator,bool> insert (const value_type& val) {
		if (DEBUG) std::cerr << "insert:   " << val.first << ' ' << val.second << std::endl;

		//std::cerr << "ICI\n";

		size_t backup = _size;
		insert_node_check_root(val, _root);
		return (pair<iterator,bool>(position_of_a_key(val.first), backup != _size));
	}
	iterator insert (iterator position, const value_type& val) {
		(void)position;
		insert_node_check_root(val, _root);
		return iterator(position_of_a_key(val.first));
	}
	template <class InputIterator>
	void insert (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
		for (;first != last; first++)
			insert(*first);
	}
	void erase (iterator position) {
		erase(position->first);
	}
	size_type erase (const key_type& k) {
		size_type backup = _size;
		_root = delete_node(_root, k);
		return backup - _size;
	}
	void erase (iterator first, iterator last) {
		map<key_type, mapped_type> temp(first, last);
		iterator it = temp.begin();
		iterator ite = temp.end();
		for (; it != ite; it++)
			delete_node(_root, it->first);
	}
	void swap (map& x) {
		node_allocator temp_alloc_type = _alloc_type;
		key_compare temp_key_compare = _key_compare;
		size_type temp_size = _size;
		node_type *temp_root = _root;
		_alloc_type = x._alloc_type;
		_key_compare = x._key_compare;
		_size = x._size;
		_root = x._root;
		x._alloc_type = temp_alloc_type;
		x._key_compare = temp_key_compare;
		x._size = temp_size;
		x._root = temp_root;
	}
	void clear() {
		clear_from_node(_root);
	}

//OBSERVERS
	key_compare key_comp() const {return _key_compare;}
	value_compare value_comp() const {return value_compare(key_compare());}

//OPERATIONS
	iterator find (const key_type& k) {
		node_type *temp = position_of_a_key(k);
		if (temp)
			return iterator(temp);
		return end();
	}
	const_iterator find (const key_type& k) const {
		node_type *temp = const_position_of_a_key(k);
		if (temp)
			return const_iterator(temp);
		return end();
	}
	size_type count (const key_type& k) const {//1 if found, 0 otherwise, use find
		node_type *temp = const_position_of_a_key(k);
		if (temp)
			return 1;
		return 0;
	}
	iterator lower_bound (const key_type& k) {
		iterator ite = end();
		for (iterator it = begin(); it != ite; it++)
			if (!_key_compare(it->first, k))
				return it;
		return ite;
	}
	const_iterator lower_bound (const key_type& k) const {
		const_iterator ite = end();
		for (const_iterator it = begin(); it != ite; it++)
			if (!_key_compare(it->first, k))
				return const_iterator(it);
		return ite;
	}
	iterator upper_bound (const key_type& k) {
		iterator ite = end();
		for (iterator it = begin(); it != ite; it++)
			if (_key_compare(k, it->first))
				return it;
		return ite;
	}
	const_iterator upper_bound (const key_type& k) const {
		const_iterator ite = end();
		for (const_iterator it = begin(); it != ite; it++)
			if (_key_compare(k, it->first))
				return const_iterator(it);
		return ite;		
	}
	pair<iterator,iterator> equal_range (const key_type& k) {
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}

//ALLOCATORS
	allocator_type get_allocator() const {return _alloc_type;}

//TREE
	void print_all() {
		print(_root);
	}

private:

	void print(node_type *start, std::string path = "") {
		if (start) {
			print(start->left, path + "L");
			std::cout << path << ' ' << start->value.first << '_' << start->value.second;
			if (start->parent)
				std::cout << " p:" << start->parent->value.first << ' ';
			else
				std::cout << " root";
			if (start->left || start->right) {
				std::cout << " ";
				if (start->left)
					std::cout << "l";
				if (start->right)
					std::cout << "r";
			}
			if (start->last)
				std::cout << " last";
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

/*
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
*/
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

	//void insert_node_check_root(const value_type& val, node_type *current, node_type *parent = NULL);

	node_type* insert_node_check_root(const value_type& val, node_type *current, node_type *parent = NULL) {
		if (!_root) {
			_root = new_node(val, NULL);
			if(DEBUG) std::cerr << "                      GENERATED LAST\n";
			node_type *last = new_node(val, _root); //dummy value in the last node
			_size--;
			_root->right = last;
			last->last = true;
			if(DEBUG) std::cerr << _root->last << ' ' << _root->right->last << std::endl;
			return _root;
		}
		if (_root->last) {
			node_type *new_root = new_node(val, NULL);
			_root->parent = new_root;
			new_root->right = _root;
			_root = new_root;
			return _root;
		}
		return insert_node(val, current, parent);
	}

	node_type* insert_node(const value_type& val, node_type *current, node_type *parent) {
		if (!current)
			return new_node(val, parent);
		if (current->last) {
			if(DEBUG) std::cerr << val.first << ' ' << val.second << ' ' << current->value.first << ' ' << parent->value.first << "\n";
			node_type *to_insert = new_node(val, parent);
			current->parent = to_insert;
			to_insert->right = current;
			current = to_insert;
			return current;
		}
		if (_key_compare(val.first, current->value.first))
			current->left = insert_node(val, current->left, current);
		else if (_key_compare(current->value.first, val.first))
			current->right = insert_node(val, current->right, current);
		else
			return current;

/*
		current->height = 1 + max(height(current->left), height(current->right));
		//rotate here if neccessary
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
		//return current; //retirer
		if (!current || current->last)
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
					//std::cerr << "uwuwuwuwuwuwu\n";
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
				_size--;
				/*
				node_type *temp = min_value_node(current->right);
				current->value = temp->value;
				current->right = delete_node(current->right, key);
				*/
				//std::cerr << "problem 2 child\n";
				current = temp;
			}
		}

	//	if (!current)
	//		return current;
//		current->height = 1 + max(height(current->left), height(current->right));
		//rotate here if necessary
		return current;
	}

	void clear_from_node(node_type *current) {
		if (current) {
			clear_from_node(current->left);
			clear_from_node(current->right);
			_alloc_type.destroy(current);
			_alloc_type.deallocate(current, 1);
			if (_size > 0)
				_size--;
			if (current == _root)
				_root = NULL;
		}
	}

	node_type* position_of_a_key(const key_type& key) { //passer en mode insert_node pour plus d'opti car cette fonction est appelee souvent
		iterator ite = end();
		for (iterator it = begin(); it != ite; it++)
			if (it->first == key)
				return it.get_node();
		return NULL;
	}

	node_type* const_position_of_a_key(const key_type& key) const { //passer en mode insert_node pour plus d'opti car cette fonction est appelee souvent
		const_iterator ite = end();
		for (const_iterator it = begin(); it != ite; it++)
			if (it->first == key)
				return it.get_node();
		return NULL;
	}

};

//NON-MEMBER FUNCTION OVERLOADS
	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {return !(lhs == rhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {return (lhs < rhs || lhs == rhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {return rhs < lhs;}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {return (lhs > rhs || lhs == rhs);}
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {x.swap(y);}

}

#endif

/*
const ft::map<>
int, foo<int>, std::__1::less<int>, std::__1::allocator<ft::pair<const int, foo<int> > > 

ft::map<>::operator[](char const&)
char, int, std::__1::less<char>, std::__1::allocator<ft::pair<char const, int> > 


const ft::map<>
int, 
std::__1::basic_string<char>, 
ft::less<int>,
std::__1::allocator<ft::pair<const int, std::__1::basic_string<char> > > 







const map_iterator<ft::pair<const char, int>, ft::node<ft::pair<const char, int> > *>






*/