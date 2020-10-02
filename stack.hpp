#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack {
public:
	typedef T			value_type;
	typedef Container	container_type;
	typedef std::size_t	size_type;

protected:
	container_type c;

public:
	// constructor
	explicit stack(container_type const & ctnr = container_type()) : c(ctnr) {}
	~stack() {}

	bool 		empty() const { return this->c.empty(); }
	size_type	size() const { return this->c.size(); }

	value_type&			top() { return this->c.back(); }
	const value_type&	top() const { return this->c.back(); }

	void push(value_type const &val) { this->c.push_back(val); }
	void pop() { this->c.pop_back(); }

	friend	bool	operator==(stack<T, Container> const & lhs, stack<T, Container> const & rhs) { return lhs.c == rhs.c; }
	friend	bool	operator!=(stack<T, Container> const & lhs, stack<T, Container> const & rhs) { return lhs.c != rhs.c; }
	friend	bool	operator<(stack<T, Container> const & lhs, stack<T, Container> const & rhs) { return lhs.c < rhs.c; }
	friend	bool	operator<=(stack<T, Container> const & lhs, stack<T, Container> const & rhs) { return lhs.c <= rhs.c; }
	friend	bool	operator>(stack<T, Container> const & lhs, stack<T, Container> const & rhs) { return lhs.c > rhs.c; }
	friend	bool	operator>=(stack<T, Container> const & lhs, stack<T, Container> const & rhs) { return lhs.c >= rhs.c; }

};

}; //end of namespace ft

#endif
