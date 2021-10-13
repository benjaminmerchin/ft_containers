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
template <typename Iterator>
class iterator_traits {
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
};

template <typename T>
class iterator_traits <T *> {
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
};

template <typename T>
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
}

