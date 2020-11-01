#ifndef TREENODE_HPP
# define TREENODE_HPP

# include "colour.hpp"

namespace ft
{

template <class T>
struct treeNode
{
	T			*value;
	treeNode	*left;
	treeNode	*right;
	treeNode	*parent;
	enum Colour	colour;

	treeNode(): value(new T()), left(0), right(0), parent(0), colour(RED) {}
	treeNode(T const & val): value(new T(val)), left(0), right(0), parent(0), colour (RED) {}
	treeNode(treeNode const & other): value(0) { *this = other; }
	treeNode(enum Colour col): value(new T()), left(0), right(0), parent(0), colour(col) {}
	~treeNode() { delete this->value; }
	treeNode&	operator=(treeNode const & rhs)
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
