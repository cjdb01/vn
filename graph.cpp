#include "graph.hpp"

#include <algorithm>
#include <queue>

using namespace std;

node::node(char v, node* ptr) : n(v), p(ptr) { }

edge::edge(char f, char t, const size_t w, size_t l) : a(f), b(t), weight(w), load(l) { }

graph::graph(istream& in)
{
    char from, to;
    size_t weight, max_load;
    while (!in.eof())
    {
        in >> from;
        in.get();
        in >> to;
        in.get();
        in >> weight;
        in.get();
        in >> max_load;

        edge *e = new edge(from, to, weight, max_load);
        
        m_adj[from].push_back(e);
        m_adj[to].push_back(e);
    }
}

vector<node*> graph::shp(char from, char to)
{
    queue<node*> to_visit;
    vector<node*> visited;
    
    to_visit.push(new node { from, nullptr } );
    
    while (!to_visit.empty())
    {
        auto n = to_visit.front();
        visited.push_back(n);
        to_visit.pop();
        
        if (n->n == to)
        {
            return visited;
        }
        else
        {
            for (auto i = m_adj[n->n].begin(); i != m_adj[n->n].end(); ++i)
            {
                auto count = 0;
            
                for (auto it = visited.begin(); it != visited.end(); ++it)
                {
                    if (n->n == (*i)->a)
                        count = (*i)->b == (*it)->n ? 1 : 0;
                    else
                        count = (*i)->a == (*it)->n ? 1 : 0;
                }
            
                if (count == 0)
                {
                    auto v = (*i)->a == n->n ? (*i)->b : (*i)->a;
                    to_visit.push(new node{v, visited.front()});
                }
            }
        }
    }
    return vector<node*>();
}

int main()
{
    graph g(std::cin);
    auto s = g.shp('A', 'D');
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        cout << (*it)->n << endl;
    }
    
    return 0;
}