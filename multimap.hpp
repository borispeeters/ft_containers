#ifndef MULTIMAP_HPP
# define MULTIMAP_HPP

# include <functional>
# include <memory>
# include <utility>

# include "iterator.hpp"
# include "mapIterator.hpp"

namespace ft
{

template <class Key,											// multimap::key_type
		class T,												// multimap::mapped_type
		class Compare = std::less<Key>,							// multimap::key_compare
		class Alloc = std::allocator<std::pair<const Key, T> >	// multimap::allocator_type
		>
class multimap
{
public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef std::pair<const key_type, mapped_type>					value_type;
	typedef Compare													key_compare;
//	typedef lol														value_compare;
	typedef Alloc													allocator_type;
	typedef	typename allocator_type::reference						reference;
	typedef	typename allocator_type::const_reference				const_reference;
	typedef	typename allocator_type::pointer						pointer;
	typedef	typename allocator_type::const_pointer					const_pointer;
	typedef ft::mapIterator<value_type>								iterator;
	typedef ft::constMapIterator<value_type>						const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

	struct value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class multimap;
	protected:
		Compare comp;
		value_compare(Compare c): comp(c) {}
	public:
		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool operator()(value_type const & x, value_type const & y) const { return comp(x.first, y.first); }
	};

private:
	mapNode<value_type>*	m_root;
};

}; //end of namespace ft

#endif
