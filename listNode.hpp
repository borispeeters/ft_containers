#ifndef LISTNODE_HPP
# define LISTNODE_HPP

namespace ft
{

template <class T>
struct listNode
{
	T			*data;
	listNode	*prev;
	listNode	*next;

	listNode():	data(0), prev(0), next(0) {}
	listNode(T const & val): data(new T(val)), prev(0), next(0) {}
	listNode(listNode const & other): data(0) { *this = other; }
	~listNode() { delete this->data; }
	listNode&	operator=(listNode const & other)
	{
		if (&other != this)
		{
			delete this->data;
			this->data = new T(other.data);
			this->prev = other.prev;
			this->next = other.next;
		}
		return *this;
	}
};

}; //end of namespace ft

#endif
