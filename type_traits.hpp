#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

}; //end of namespace ft

#endif
