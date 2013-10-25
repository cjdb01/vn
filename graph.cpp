#include "graph.hpp"

#include <functional>
#include <queue>
#include <set>
#include <vector>

using namespace std;

namespace pipe
{
	bool operator==(const graph::edge& lhs, const graph::edge& rhs)
	{
		return lhs.destination == rhs.destination;
	}

	bool operator<(const graph::edge& lhs, const graph::edge& rhs)
	{
		return lhs.weight < rhs.weight;
	}

	graph::graph(istream& in)
	{
		char source;
		edge e;
		while (!in.eof())
		{
			in >> source;
			in.get();
			in >> e.destination;
			in.get();
			in >> e.weight;
			in.get();
			in >> e.max_connections;

			m_adjacencyList[source].insert(e);

			std::swap(e.destination, source);
			m_adjacencyList[source].insert(e);
		}
	}

	set<char> graph::ucs(const char from, const char to)
	{
		priority_queue<pair<char, size_t>> to_visit;
		set<char> visited;

		to_visit.push( { from, 0 } );
		char current;

		while (to_visit.empty() == false)
		{
			current = to_visit.top().first;
			to_visit.pop();
			if (current == to)
				return visited;

			visited.insert(current);

			for (auto it = m_adjacencyList[current].cbegin(); it != m_adjacencyList[current].cend(); ++it)
			{
				if (visited.lower_bound(it->destination) == visited.end())
					to_visit.push( { it->destination, it->weight } );
			}
		}

		return set<char>();
	}
}

using namespace pipe;
#include <fstream>
int main()
{
	std::ifstream i("input.txt", ifstream::in);
	graph g(i);

	auto s = g.ucs('A', 'D');

	for (auto it = s.cbegin(); it != s.cend(); ++it)
	{
		cout << *it << endl;
	}

	return 0;
}