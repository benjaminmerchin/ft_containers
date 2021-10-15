#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace ft {

//https://en.cppreference.com/w/cpp/types/enable_if
template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

//https://www.cplusplus.com/reference/type_traits/is_integral/
template<class T>
struct is_integral { const static bool value = false; };

template<>
struct is_integral<bool> { const static bool value = true; };
template<>
struct is_integral<char> { const static bool value = true; };
template<>
struct is_integral<char16_t> { const static bool value = true; };
template<>
struct is_integral<char32_t> { const static bool value = true; };
template<>
struct is_integral<wchar_t> { const static bool value = true; };
template<>
struct is_integral<signed char> { const static bool value = true; };
template<>
struct is_integral<short int> { const static bool value = true; };
template<>
struct is_integral<int> { const static bool value = true; };
template<>
struct is_integral<long int> { const static bool value = true; };
template<>
struct is_integral<long long int> { const static bool value = true; };
template<>
struct is_integral<unsigned char> { const static bool value = true; };
template<>
struct is_integral<unsigned short int> { const static bool value = true; };
template<>
struct is_integral<unsigned int> { const static bool value = true; };
template<>
struct is_integral<unsigned long int> { const static bool value = true; };
template<>
struct is_integral<unsigned long long int> { const static bool value = true; };

//typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first
//std::numeric_limits<InputIterator>::is_integer, InputIterator>
//std::numeric_limits<int>::is_integer, int> -> true
//std::numeric_limits<float>::is_integer, float> -> false

//https://www.cplusplus.com/reference/iterator/iterator_traits/
template <class Iterator>
class iterator_traits {
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits <T *> {
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits <const T *> {
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
};

// member             generic definition           T* specialization            const T* specialization
// difference_type    Iterator::difference_type    ptrdiff_t                    ptrdiff_t
// value_type         Iterator::value_type         T                            T
// pointer            Iterator::pointer            T*                           const T*
// reference          Iterator::reference          T&                           const T&
// iterator_category  Iterator::iterator_category  random_access_iterator_tag   random_access_iterator_tag

//https://cplusplus.com/reference/algorithm/lexicographical_compare/?kw=lexicographical_compare
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
	while (first1!=last1) {
		if (first2==last2 || *first2<*first1)
			return false;
		else if (*first1<*first2)
			return true;
		++first1; ++first2;
	}
	return (first2!=last2);
}

//https://cplusplus.com/reference/algorithm/equal/
template <class InputIterator1, class InputIterator2>
bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
	while (first1!=last1) {
		if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
			return false;
		++first1; ++first2;
	}
	return true;
}

}

#endif