#ifdef _FT_LIST_HPP

#ifndef _FT_LISTNODE_HPP
# define _FT_LISTNODE_HPP

# include <cstddef>

namespace ft
{

template <class T>
struct listNode
{
	T			data;
	listNode	*prev;
	listNode	*next;

	listNode(T const & val = T()): data(val), prev(NULL), next(NULL) {}

	listNode(listNode const & other): data() {
		*this = other;
	}

	~listNode() {}

	listNode&	operator=(listNode const & other) {
		if (&other != this) {
			this->data = other.data;
			this->prev = other.prev;
			this->next = other.next;
		}
		return *this;
	}
};

} //end of namespace ft

#endif

# else
# error "This is an internal node used by the ft::list class and is not intended to be included directly."
#endif
