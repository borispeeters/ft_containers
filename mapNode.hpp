#ifndef MAPNODE_HPP
# define MAPNODE_HPP

# include "colour.hpp"

namespace ft
{

template <class Pair>
struct mapNode
{
	Pair		*value;
	mapNode		*left;
	mapNode		*right;
	mapNode		*parent;
	enum Colour	colour;

	mapNode(): value(new Pair()), left(0), right(0), parent(0), colour(RED) {}
	mapNode(Pair const & val): value(new Pair(val)), left(0), right(0), parent(0), colour(RED) {}
	mapNode(mapNode const & other): value(0) { *this = other; }
	mapNode(enum Colour col): value(new Pair()), left(0), right(0), parent(0), colour(col) {}
	~mapNode() { delete this->value; }
	mapNode&	operator=(mapNode const & rhs)
	{
		if (&rhs!= this)
		{
			delete this->value;
			this->value = new Pair(rhs.value);
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
