#ifndef EXAMPLE_HPP
# define EXAMPLE_HPP

# include <iostream>

class Example
{
	int x;

public:
	Example();
	Example(Example const & x);
	Example(Example && x);
	~Example();

	Example&	operator=(Example const & rhs);
};

#endif
