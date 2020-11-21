#ifndef EXAMPLE_HPP
# define EXAMPLE_HPP

# include <iostream>

struct Example
{
	Example();
	Example (Example const & other);
	~Example();

	Example&	operator=(Example const & rhs);
};

#endif
