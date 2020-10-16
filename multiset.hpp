#ifndef MULTISET_HPP
# define MULTISET_HPP

# include <functional>
# include <memory>

# include "iterator.hpp"

namespace ft
{

template <class T,						// multiset::key_type/value_type
		class Compare = std::less<T>,	// multiset::key_compare/value_compare
		class Alloc = std::allocator<T>	// multiset::allocator_type
		>
class multiset
{
public:
	typedef T														key_type;
	typedef T														value_type;
	typedef Compare													key_compare;
	typedef Compare													value_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
//	typedef ft::setIterator<value_type>								iterator;
//	typedef ft::constSetIterator<value_type>						const_iterator;
//	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
//	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
//	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type						size_type;

private:
	// vars

public:
	// stoof
};

}; //end of namespace ft

#endif
