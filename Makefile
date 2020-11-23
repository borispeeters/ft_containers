NAME = ft_containers
INC = ftl
CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++98 -g

vector list map multimap set multiset stack queue: fclean
	$(CXX) $(CXXFLAGS) $@Test.cpp Timer.cpp -o $(NAME) -I$(INC)

clean:

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM
