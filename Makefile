CONTAINERS := vector list deque map multimap set multiset stack queue
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++98

all: $(CONTAINERS)

$(CONTAINERS): % : tests/%Test.cpp
	$(CXX) $(CXXFLAGS) tests/$@Test.cpp -o $@ -Iinclude

clean:

fclean: clean
	@for container in $(CONTAINERS) ; do \
		echo "$(RM) $$container" ; \
		$(RM) $$container ; \
	done

re: fclean all
