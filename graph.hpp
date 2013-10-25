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
#include <map>
#include <set>
#include <string>

namespace pipe
{
	class graph
	{
	private:
		struct edge
		{
			char destination;
			size_t weight;
			size_t max_connections;

			
		};

		std::map<char, std::set<edge>> m_adjacencyList;
	public:
		graph(std::istream&);

		std::set<char> ucs(const char from, const char to);

		friend bool operator==(const edge&, const edge&);
		friend bool operator<(const edge&, const edge&);
	};
}

#endif // GRAPH_HPP_11_INCLUDED