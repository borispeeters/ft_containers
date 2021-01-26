#ifdef _FT_LIST_HPP

#ifndef _FT_LISTNODE_HPP
# define _FT_LISTNODE_HPP

# include <cstddef>

namespace ft
{

template <class T, class Alloc>
struct listNode
{
	T			*data;
	listNode	*prev;
	listNode	*next;
	Alloc		alloc;

	listNode(Alloc const & a = Alloc()): data(NULL), prev(NULL), next(NULL), alloc(a) {
		this->data = this->alloc.allocate(1);
	}
	listNode(T const & val, Alloc const & a = Alloc()): data(NULL), prev(NULL), next(NULL), alloc(a) {
		this->data = this->alloc.allocate(1);
		this->alloc.construct(this->data, val);
	}
	listNode(listNode const & other): data(NULL), alloc(other.alloc) {
		this->data = this->alloc.allocate(1);
		*this = other;
	}
	~listNode() {
		this->alloc.destroy(this->data);
		this->alloc.deallocate(this->data, 1);
	}
	listNode&	operator=(listNode const & other)
	{
		if (&other != this)
		{
			this->alloc.destroy(this->data);
			this->alloc.construct(this->data, *(other.data));
			this->prev = other.prev;
			this->next = other.next;
			this->alloc = other.alloc;
		}
		return *this;
	}
};

} //end of namespace ft

#endif

# else
# error "This is an internal node used by the ft::list class and is not intended to be included directly."
#endif
