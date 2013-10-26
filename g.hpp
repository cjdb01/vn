#ifndef GRAPH_HPP11_INCLUDED
#define GRAPH_HPP11_INCLUDED

#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <stack>
#include <vector>

struct node { char n; node* p; node(char, node*); };

struct edge { char a; char b; const size_t weight; size_t load; size_t max_load; edge(char, char, size_t, size_t); };

class graph
{
private:
    std::map<char, std::list<edge*>> m_adj;
	std::map<size_t, std::vector<edge*>> m_connection;

	std::stack<node*> sanitise(const std::vector<node*>&) const;

	std::default_random_engine        m_random;
public:
    graph(std::istream&);
    
    std::vector<node*> shp(char from, char to);
	std::vector<node*> sdp(char from, char to);
	std::vector<node*> llp(char from, char to);
	std::pair<size_t, size_t> establish_connection(const size_t& time, const std::vector<node*>& n);
	inline void abolish_connection(const size_t& time);
};

#endif // GRAPH_HPP11_INCLUDED