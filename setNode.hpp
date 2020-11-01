#ifndef SETNODE_HPP
# define SETNODE_HPP

# include "colour.hpp"

namespace ft
{

template <class T>
struct setNode
{
	T			*value;
	setNode		*left;
	setNode		*right;
	setNode		*parent;
	enum Colour	colour;

	setNode(): value(new T()), left(0), right(0), parent(0), colour(RED) {}
	setNode(T const & val): value(new T(val)), left(0), right(0), parent(0), colour(RED) {}
	setNode(setNode const & other): value(0) { *this = other; }
	setNode(enum Colour col): value(new T()), left(0), right(0), parent(0), colour(col) {}
	~setNode() { delete this->value; }
	setNode&	operator=(setNode const & rhs)
	{
		if (&rhs != this)
		{
			delete this->value;
			this->value = new T(rhs.value);
			this->left = rhs.left;
			this->right = rhs.right;
			this->parent = rhs.parent;
			this->colour = rhs.colour;
		}
		return *this;
	}
};

}; //end of namespace ft

#endif
