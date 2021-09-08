#include <memory>
#include <iostream>
#include <string>



//vector is a sequence container that encapsulates dynamic size arrays

namespace ft {

template<class T, class Allocator = std::allocator<T> >
class vector {
public:

/* -------------------------------------------------- */
/*              CONSTRUCTOR / DESTRUCTOR              */
/* -------------------------------------------------- */

	//4 constructors required : empty/fill/range/copy
	vector() {
		content = NULL;
	}
	vector(T const src){(void)src;}
	~vector(){}
/* -------------------------------------------------- */
/*                      OPERATOR                      */
/* -------------------------------------------------- */

/* -------------------------------------------------- */
/*                 GETTERS / SETTERS                  */
/* -------------------------------------------------- */

/* -------------------------------------------------- */
/*                  MEMBER FUNCTIONS                  */
/* -------------------------------------------------- */

protected:
	T * content;

};

}
