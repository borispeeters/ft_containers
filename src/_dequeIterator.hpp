#ifdef _FT_DEQUE_HPP

#ifndef _FT_DEQUEITERATOR_HPP
# define _FT_DEQUEITERATOR_HPP

# include <cstddef>
# include "iterator.hpp"

namespace ft
{

template <class T, std::size_t Size>
class dequeIterator : public ft::iterator<ft::random_access_iterator_tag, T>
{

	template <class, class> friend class deque;

public:
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;
	typedef value_type*						pointer;
	typedef value_type&						reference;
	typedef const value_type*				const_pointer;
	typedef const value_type&				const_reference;
	typedef ft::random_access_iterator_tag	iterator_category;

protected:
	typedef pointer*						map_pointer;

	pointer 	m_cur;
	pointer 	m_first;
	pointer 	m_last;
	map_pointer	m_node;

public:
	dequeIterator() {}
	dequeIterator(dequeIterator const & other) { *this = other; }

	dequeIterator&	operator=(dequeIterator const & rhs) {
		if (&rhs != this) {
			this->m_cur = rhs.m_cur;
			this->m_first = rhs.m_first;
			this->m_last = rhs.m_last;
			this->m_node = rhs.m_node;
		}
		return *this;
	}

	virtual ~dequeIterator() {}

	dequeIterator&	operator++() {
		++this->m_cur;
		if (this->m_cur == this->m_last) {
			this->setNode(this->m_node + 1);
			this->m_cur = this->m_first;
		}
		return *this;
	}

	dequeIterator	operator++(int) {
		dequeIterator	tmp = *this;
		++(*this);
		return tmp;
	}

	dequeIterator&	operator--() {
		if (this->m_cur == this->m_first) {
			this->setNode(this->m_node - 1);
			this->m_cur = this->m_last;
		}
		--this->m_cur;
		return *this;
	}

	dequeIterator	operator--(int) {
		dequeIterator	tmp = *this;
		--(*this);
		return tmp;
	}

	dequeIterator&	operator+=(difference_type rhs) {
		difference_type	offset = rhs + (this->m_cur - this->m_first);
		if (offset >= 0 && offset < difference_type(this->chunk_size()))
			this->m_cur += rhs;
		else {
			difference_type	node_offset;
			if (offset > 0) node_offset = offset / difference_type(this->chunk_size());
			else node_offset = -((-offset - 1) / difference_type(this->chunk_size())) -1;

			this->setNode(this->m_node + node_offset);
			this->m_cur = this->m_first + (offset - node_offset * this->chunk_size());
		}
		return *this;
	}

	dequeIterator	operator+(difference_type rhs) {
		dequeIterator	tmp = *this;
		return tmp += rhs;
	}

	dequeIterator&	operator-=(difference_type rhs) { return *this += -rhs; }

	dequeIterator	operator-(difference_type rhs) const {
		dequeIterator	tmp = *this;
		return tmp -= rhs;
	}

	difference_type	operator-(dequeIterator const & rhs) const {
		return Size * (this->m_node - rhs.m_node - 1) + (this->m_cur - this->m_first)
		+ (rhs.m_last - rhs.m_cur);
	}

	reference	operator[](difference_type idx) { return *(*this + idx); }
	pointer 	operator->() { return this->m_cur; }
	reference	operator*() { return *this->m_cur; }

	friend bool	operator==(dequeIterator const & lhs, dequeIterator const & rhs) { return lhs.m_cur == rhs.m_cur; }
	friend bool	operator!=(dequeIterator const & lhs, dequeIterator const & rhs) { return !(lhs == rhs); }
	friend bool	operator<(dequeIterator const & lhs, dequeIterator const & rhs) {
		return lhs.m_node < rhs.m_node && lhs.m_cur < rhs.m_cur;
	}
	friend bool	operator>(dequeIterator const & lhs, dequeIterator const & rhs) { return rhs < lhs; }
	friend bool	operator<=(dequeIterator const & lhs, dequeIterator const & rhs) { return !(rhs < lhs); }
	friend bool	operator>=(dequeIterator const & lhs, dequeIterator const & rhs) { return !(lhs < rhs); }

protected:
	void	setNode(map_pointer new_node) {
		this->m_node = new_node;
		this->m_first = *new_node;
		this->m_last = this->m_first + this->chunk_size();
	}

	size_type	chunk_size() const { return Size; }
};

template <class T, std::size_t Size>
class constDequeIterator : public dequeIterator<T, Size>
{
public:
	typedef	T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef value_type*						pointer;
	typedef const value_type*				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef ft::random_access_iterator_tag	iterator_category;

	constDequeIterator(): dequeIterator<value_type, Size>() {}
	constDequeIterator(dequeIterator<value_type, Size> const & other): dequeIterator<value_type, Size>(other) {}
	constDequeIterator(constDequeIterator const & other): dequeIterator<value_type, Size>(other) {}

	constDequeIterator&	operator=(dequeIterator<value_type, Size> const & rhs) {
		dequeIterator<value_type, Size>::operator=(rhs);
		return *this;
	}

	constDequeIterator&	operator=(constDequeIterator const & rhs) {
		dequeIterator<value_type, Size>::operator=(rhs);
		return *this;
	}

	virtual ~constDequeIterator() {}

	const_reference	operator[](difference_type idx) const { return *(*this + idx); }
	const_pointer	operator->() const { return this->m_cur; }
	const_reference	operator*() const { return *this->m_cur; }
};

} //end of namespace ft

#endif

#else
# error "Please include deque.hpp to access its iterator."
#endif
