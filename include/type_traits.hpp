#ifndef _FT_TYPE_TRAITS_HPP
# define _FT_TYPE_TRAITS_HPP

namespace ft
{

template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template <class>
struct _void_t { typedef void type; };

} //end of namespace ft

#endif
