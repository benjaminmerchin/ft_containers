#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <string>
#include "pair.hpp"

namespace ft {

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
    //typedef     Nested function class to compare elements   value_compare;
    typedef Alloc                                        allocator_type;
    typedef typename allocator_type::reference           reference;
    typedef typename allocator_type::const_reference     const_reference;
    typedef typename allocator_type::pointer             pointer;
    typedef typename allocator_type::constpointer        const_pointer;
    typedef typename allocator_type::size_type           size_type;
    typedef typename allocator_type::difference_type     difference_type;
    typedef vector_iterator<value_type>                  iterator;
	typedef vector_iterator<value_type const>            const_iterator;
	typedef ft::reverse_iterator<iterator>               reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;
/*
    iterator	a bidirectional iterator to value_type	convertible to const_iterator
    const_iterator	a bidirectional iterator to const value_type	
    reverse_iterator	reverse_iterator<iterator>	
    const_reverse_iterator	reverse_iterator<const_iterator>
*/

protected:
	allocator_type _alloc_type;
    key_compare _key_compare;

private:
//CONSTRUCTORS
    //empty (1)	
    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _alloc_type(alloc) {}
    //range (2)	
    template <class InputIterator>
    map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _alloc_type(alloc) {
        (void)first;
        (void)last;
    }
    //copy (3)	
    map (const map& x) : _alloc_type(x._alloc_type), _key_compare(x._key_compare) {}
    ~map () {}
    map& operator= (const map& x) {
        (void)x;
    }

//ITERATORS

//CAPACITY

//ELEMENT ACCESS

//MODIFIERS

//OBSERVERS

//OPERATIONS

//ALLOCATORS



};
/*
*/
}

#endif
