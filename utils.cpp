#include <iostream>


namespace ft {

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { 
	typedef T type; 
};

//https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
template<typename T>
struct numeric_limits { bool is_integer() {return false;} };

template<>
struct numeric_limits<bool> { bool is_integer() {return true;} };
template<>
struct numeric_limits<char> { bool is_integer() {return true;} };
template<>
struct numeric_limits<signed char> { bool is_integer() {return true;} };
template<>
struct numeric_limits<unsigned char> { bool is_integer() {return true;} };
template<>
struct numeric_limits<int> { bool is_integer() {return true;} };
template<>
struct numeric_limits<unsigned int> { bool is_integer() {return true;} };
template<>
struct numeric_limits<long> { bool is_integer() {return true;} };
template<>
struct numeric_limits<unsigned long> { bool is_integer() {return true;} };
template<>
struct numeric_limits<float> { bool is_integer() {return false;} };
template<>
struct numeric_limits<double> { bool is_integer() {return false;} };
template<>
struct numeric_limits<long double> { bool is_integer() {return false;} };

}

//typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first
//std::numeric_limits<InputIterator>::is_integer, InputIterator>
//std::numeric_limits<int>::is_integer, int> -> true
//std::numeric_limits<float>::is_integer, float> -> false

/* non-specialized *//*	false
bool	true
char	true
signed char	true
unsigned char	true
wchar_t	true
short	true
unsigned short	true
int	true
unsigned int	true
long	true
unsigned long	true
float	false
double	false
long double	false*/