#ifndef GRAPH_HPP_11_INCLUDED
#define GRAPH_HPP_11_INCLUDED

/*
 * Christopher Di Bella
 * <chrisdb@cse.unsw.edu.au>
 *
 * 25 October, 2013
 *
 * This is a C++11 header, subject to GCC 4.7.2 as on CSE machines
 */
#include <iostream>
#include <list>
#include <map>
#include <string>

namespace pipe
{
	class network
	{
	private:
		struct node
		{
			char value;
			size_t max_connections;
			size_t distance;
		};

		std::map<char, std::list<node*>> m_adjacencyList;
	public:
		network(std::istream& in);
		~network();

		size_t path_exists(char source, char dest);
	};
}

#endif // GRAPH_HPP_11_INCLUDED