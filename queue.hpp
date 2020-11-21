#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <cstddef>
# include "functional.hpp"
# include "iterator.hpp"
# include "list.hpp"
# include "vector.hpp"

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



# include <algorithm>

template <class T, class Container = ft::vector<T>, class Compare = ft::less<typename Container::value_type> >
class priority_queue
{
public:
	typedef T			value_type;
	typedef Container	container_type;
	typedef std::size_t	size_type;

protected:
	container_type	c;
	Compare			comp;

public:
	// 1. initialization constructor
	explicit priority_queue(Compare const & cmpr = Compare(), container_type const & ctnr = container_type()):
		c(ctnr), comp(cmpr)
	{
		std::make_heap(this->c.begin(), this->c.end(), this->comp);
	}

	// 2. range constructor
	template <class Iterator>
	priority_queue(Iterator first, Iterator last,
				   Compare const & cmpr = Compare(), container_type const & ctnr = container_type(),
				   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0):
				   c(ctnr), comp(cmpr)
	{
		this->c.insert(this->c.end(), first, last);
		std::make_heap(this->c.begin(), this->c.end(), this->comp);
	}

	// 3. copy constructor
	priority_queue(priority_queue const & other): c(other.c), comp(other.comp)
	{
		std::make_heap(this->c.begin(), this->c.end(), this->comp);
	}

	~priority_queue() {}

	priority_queue&	operator=(priority_queue const & rhs)
	{
		if (&rhs != this)
		{
			this->comp = rhs.comp;
			this->c = rhs.c;
		}
		return *this;
	}

	bool		empty() const { return this->c.empty(); }
	size_type	size() const { return this->c.size(); }

	const value_type&	top() const { return this->c.front(); }

	void push(value_type const & val)
	{
		this->c.push_back(val);
		std::push_heap(this->c.begin(), this->c.end(), this->comp);
	}
	void pop()
	{
		std::pop_heap(this->c.begin(), this->c.end(), this->comp);
		this->c.pop_front();
	}
};

}; //end of namespace ft

#endif
