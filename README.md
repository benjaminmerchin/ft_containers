# ft_containers

[Great Tutorial to start vector](https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/)  
[Vector](https://en.cppreference.com/w/cpp/container/vector)  
[Allocator](https://en.cppreference.com/w/cpp/memory/allocator)  
[International Standard, cppreference alternative](https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf)  
[Red Black Tree video in french](https://www.youtube.com/watch?v=h1Z8_ebEqao)  
[Great Tutorial to understand Iterators](https://internalpointers.com/post/writing-custom-iterators-modern-cpp)

<!-- LOCAL
[Allocator with example](https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/)  
[Red Black Tree](file:///Users/bmerchin/Desktop/Introduction_to_Algorithms.pdf)

Faire d'abord Vector, ensuite Stack/Map
Si je fais l'arbre rouge et noir pour Stack/Map ca rajoute a peine 100 lignes de faire Set

The namespace will always be ft and your containers will be tested using ft::<container>.
Implelemter toutes les features meme depreciees de la version cpp98

- iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.
- provide a main.cpp which tests everything for your evaluations
- <container>.hpp
- produce one binary with only your containers and one with the same testing with STL containers
- additional functions than the ones in std containers must be private or protected



-->


<!-- NOTIONS
polymorphisme: des fonctions fonctionnent differemment en fonction du type des arguments, comme pour le constructeur de classes canoniques

tolook:

https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/

todo constructors destructors
-->

<!--
Improvement testor:
Even without configuration, the vector/ite_n0.cpp ite_n00.cpp ite_n1.cpp are correct

-->


<!--
vector/assign.cpp                  : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/at.cpp                      : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/at_const.cpp                : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/bidirect_it.cpp             : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/copy_construct.cpp          : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/erase.cpp                   : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/insert.cpp                  : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/insert2.cpp                 : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/ite.cpp                     : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/ite_arrow.cpp               : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/ite_eq_ope.cpp              : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/ite_n0.cpp                  : COMPILE: ✅ | RET: ✅ | OUT: ✅ | STD: [N]
vector/ite_n00.cpp                 : COMPILE: ✅ | RET: ✅ | OUT: ✅ | STD: [N]
vector/ite_n1.cpp                  : COMPILE: ✅ | RET: ✅ | OUT: ✅ | STD: [N]
vector/push_pop.cpp                : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/relational_ope.cpp          : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/rev_ite_construct.cpp       : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/rite.cpp                    : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/rite2.cpp                   : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/rite_arrow.cpp              : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/rite_eq_ope.cpp             : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/size.cpp                    : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
vector/swap.cpp                    : COMPILE: ❌ | RET: ❌ | OUT: ❌ | STD: [Y]
-->
