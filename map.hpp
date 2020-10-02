#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "iterator.hpp"
# include "type_traits.hpp"

namespace ft
{

template <class Key,											// map::key_type
		class T,												// map::mapped_type
		class Compare = std::less<Key>,							// map::key_compare
		class Alloc = std::allocator<std::pair<const Key, T> >	// map::allocator_type
		>
class map
{
public:
	typedef Key												key_type;
	typedef T												mapped_type;
	typedef std::pair<const key_type, mapped_type>			value_type;
	typedef Compare											key_compare;
	typedef lolwat											value_compare;
	typedef Alloc											allocator_type;
	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
//	typedef ft::mapIterator<value_type>						iterator;
//	typedef ft::mapIterator<const value_type>				const_iterator;
	typedef std::reverse_iterator<iterator>					reverse_iterator;
	typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type				size_type;



private:
	allocator_type	m_alloc;

public:
	// 1. empty constructor
	explicit map(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type());

	// 2. range constructor
	template <class Iterator>
	map(Iterator first, Iterator last,
		key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type(),
		typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0);

	// 3. copy constructor
	map(map const & other);

	// destructor
	~map();

	// assignment operator overload
	map&	operator=(map const & other)
	{
		if (&other != this)
		{

		}
		return *this;
	}

	iterator		begin();
	const_iterator	begin() const;
	iterator		end();
	const_iterator	end() const;

	reverse_iterator 		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator 		rend();
	const_reverse_iterator	rend() const;

	bool empty() const;
	size_type	size() const;
	size_type	max_size() const;

	mapped_type&	operator[](key_type const & k);

	// 1. single element insertion
	std::pair<iterator, bool>	insert(value_type const & val);

	// 2. insertion with hint
	iterator	insert(iterator position, value_type const & val);

	// 3. range insertion
	template <class Iterator>
	void		insert(Iterator first, Iterator last,
					   typename ft::_void_t<typename ft::iterator_traits<Iterator>::iterator_category>::type * = 0);


	// 1. erase iterator
	void erase(iterator position);

	// 2. erase key
	size_type	erase(key_type const & k);

	// 3. erase range
	void erase(iterator first, iterator, last);

	void swap(map & x)
	{
		map	tmp(x);
		x = *this;
		*this = tmp;
	}

	void clear();

	key_compare		key_comp() const;
	value_compare	value_comp() const;

	iterator		find(key_type const & k);
	const_iterator	find(key_type const & k);

	size_type	count(key_type const & k) const;

	iterator		lower_bound(key_type const & k);
	const_iterator	lower_bound(key_type const & k) const;

	iterator		upper_bound(key_type const & k);
	const_iterator	upper_bound(key_type const & k) const;

	std::pair<iterator, iterator>				equal_range(key_type const & k);
	std::pair<const_iterator, const_iterator>	equal_range(key_type const & k) const;

	allocator_type	get_allocator() const { return this->m_alloc; }

};

}; //end of namespace ft

#endif
