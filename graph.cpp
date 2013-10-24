#include "grpah.hpp"

#include <functional>
#include <queue>
#include <set>
#include <vector>

using namespace std;

network::network(std::istream& in)
{
	char source;
	while (!in.eof())
	{
		node* n = new node();
		in >> source;
		in.get();
		in >> n.destination;
		in.get();
		in >> n.weight;
		in.get();
		in >> n.max_connections;

		m_adjacencyList[source].push_back(n);

		node* r = new node(n);
		r.destination = source;
		source = n.destination;
		
		m_adjacenyList[source].push_back(r);
	}
}

size_t network::path_exists(char source, char dest)
{
	priority_queue<node*, vector<node*>, [] (node* lhs, node* rhs) { if (lhs->weight == rhs->weight) return 0; else if (lhs->weight < rhs->weight) return -1; else return 1; }> to_visit;
	set<char> visited;

	to_visit.push(
}