#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <cstddef>
# include "functional.hpp"
# include "iterator.hpp"
# include "list.hpp"

namespace ft
{

template <class T, class Container = ft::list<T> >
class queue
{
public:
	typedef T			value_type;
	typedef Container	container_type;
	typedef std::size_t	size_type;

protected:
	container_type	c;

public:
	explicit queue(container_type const & ctnr = container_type()) : c(ctnr) {}
	queue(queue const & other): c(other.c) {}
	~queue() {}

	queue&	operator=(queue const & rhs)
	{
		if (&rhs != this) this->c = rhs.c;
		return *this;
	}

	bool 		empty() const { return this->c.empty(); }
	size_type	size() const { return this->c.size(); }

	value_type&			front() { return this->c.front(); }
	const value_type&	front() const { return this->c.front(); }
	value_type&			back() { return this->c.back(); }
	const value_type&	back() const { return this->c.back(); }

	void push(value_type const & val) { this->c.push_back(val); }
	void pop() { this->c.pop_front(); }

	friend	bool operator==(queue<T, Container> const & lhs, queue<T, Container> const & rhs) { return lhs.c == rhs.c; }
	friend	bool operator!=(queue<T, Container> const & lhs, queue<T, Container> const & rhs) { return lhs.c != rhs.c; }
	friend	bool operator<(queue<T, Container> const & lhs, queue<T, Container> const & rhs) { return lhs.c < rhs.c; }
	friend	bool operator<=(queue<T, Container> const & lhs, queue<T, Container> const & rhs) { return lhs.c <= rhs.c; }
	friend	bool operator>(queue<T, Container> const & lhs, queue<T, Container> const & rhs) { return lhs.c > rhs.c; }
	friend	bool operator>=(queue<T, Container> const & lhs, queue<T, Container> const & rhs) { return lhs.c >= rhs.c; }

};

} //end of namespace ft

#endif
