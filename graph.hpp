#ifndef GRAPH_HPP11_INCLUDED
#define GRAPH_HPP11_INCLUDED

#include <iostream>
#include <list>
#include <map>
#include <vector>

struct node { char n; node* p; node(char, node*); };

struct edge { char a; char b; const size_t weight; size_t load; edge(char, char, size_t, size_t); };

class graph
{
private:
    std::map<char, std::list<edge*>> m_adj;
public:
    graph(std::istream&);
    
    std::vector<node*> shp(char from, char to);
};

#endif // GRAPH_HPP11_INCLUDED