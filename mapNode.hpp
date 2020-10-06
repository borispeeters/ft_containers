#ifndef MAPNODE_HPP
# define MAPNODE_HPP

# include <utility>

namespace ft
{

enum Colour { RED, BLACK };

template <class Pair>
struct mapNode
{
	Pair		*value;
	mapNode		*left;
	mapNode		*right;
	mapNode		*parent;
	enum Colour	colour;

	mapNode(): value(0), left(0), right(0), parent(0), colour(RED) {}
	mapNode(Pair const & val): value(new Pair(val)), left(0), right(0), parent(0), colour(RED) {}
	mapNode(mapNode const & other): value(0), left(0), right(0), parent(0), colour(RED) {}
	~mapNode() { delete value; }
	mapNode&	operator=(mapNode const & other)
	{
		if (&other != this)
		{
			delete value;
			this->value = new Pair(other.value);
			this->left = other.left;
			this->right = other.right;
			this->parent = other.parent;
			this->colour = other.colour;
		}
		return *this;
	}
};

}; //end of namespace ft

#endif
