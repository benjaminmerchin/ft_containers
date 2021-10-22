#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <string>
#include "pair.hpp"
#include "tree.hpp"
#include "map_iterator.hpp"

namespace ft {

template <typename T>
class node {
    T value;
    node *left;
    node *right;
    node *parent;
};

//Association of key and value_type https://cplusplus.com/reference/map/map/
template < class Key,                                           // map::key_type
           class T,                                             // map::mapped_type
           class Compare = std::less<Key>,                      // map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> > // map::allocator_type
           >
class map {

public:
    typedef Key                                          key_type;
    typedef T                                            mapped_type;
    typedef pair<const key_type,mapped_type>             value_type;
    typedef Compare                                      key_compare;
    typedef node<value_type>*                            node_type;
    //typedef     Nested function class to compare elements   value_compare;
    typedef Alloc                                        allocator_type;
    typedef typename allocator_type::reference           reference;
    typedef typename allocator_type::const_reference     const_reference;
    typedef typename allocator_type::pointer             pointer;
    typedef typename allocator_type::constpointer        const_pointer;
    typedef typename allocator_type::size_type           size_type;
    typedef typename allocator_type::difference_type     difference_type;
/*
    typedef vector_iterator<value_type>                  iterator;
	typedef vector_iterator<value_type const>            const_iterator;
	typedef ft::reverse_iterator<iterator>               reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;
    iterator	a bidirectional iterator to value_type	convertible to const_iterator
    const_iterator	a bidirectional iterator to const value_type	
    reverse_iterator	reverse_iterator<iterator>	
    const_reverse_iterator	reverse_iterator<const_iterator>
*/

protected:
	allocator_type _alloc_type;
    key_compare _key_compare;
    size_type _size;
    node_type _root;

private:
//CONSTRUCTORS
    //empty (1)	
    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _alloc_type(alloc), _size(0), _root(NULL) {}
    //range (2)	
    template <class InputIterator>
    map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _alloc_type(alloc), _size(0), _root(NULL) {
        (void)first;
        (void)last;
    }
    //copy (3)	
    map (const map& x) : _alloc_type(x._alloc_type), _key_compare(x._key_compare), _size(0), _root(NULL) {}
    ~map () {}
    map& operator= (const map& x) {
        (void)x;
    }

//ITERATORS
// iterator begin();
// const_iterator begin() const;
// iterator end();
// const_iterator end() const;
// reverse_iterator rbegin();
// const_reverse_iterator rbegin() const;
// reverse_iterator rend();
// const_reverse_iterator rend() const;

//CAPACITY
// bool empty() const;
// size_type size() const;
// size_type max_size() const;

//ELEMENT ACCESS
// mapped_type& operator[] (const key_type& k);

//MODIFIERS
// insert
pair<iterator,bool> insert (const value_type& val) {
    (void)val;
}
// erase
// swap
// clear

//OBSERVERS
// key_compare key_comp() const;
// value_compare value_comp() const;

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
// allocator_type get_allocator() const;

//TREE
private:

    void print(node_type start) {
        if (start) {
            print(start->left);
            std::cout << start->value.first << '_' << start->value.second << std::endl;
            print(start->right);
        }
    }


};
/*
*/
}

#endif
