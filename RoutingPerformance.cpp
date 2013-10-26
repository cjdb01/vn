#include "g.hpp"

#include <fstream>
#include <algorithm>
#include <iomanip>
#include <set>
#include <string>
#include <tuple>
#include <queue>

using namespace std;

node::node(char v, node* ptr) : n(v), p(ptr) { }

edge::edge(char f, char t, const size_t w, size_t l) : a(f), b(t), weight(w), load(0), max_load(l) { }

graph::graph(ifstream& in)
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
    
    to_visit.push(new node(from, nullptr));
	m_random.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> distribute(0, 100);
    while (!to_visit.empty())
    {
		if (distribute(m_random) < 50 && to_visit.size() > 1)
		{
			to_visit.pop();
		}
        auto n = to_visit.front();
        visited.push_back(n);
        to_visit.pop();
        
        if (n->n == to)
        {
            return visited;
        }
        else
        {
			auto cntr = 0;
            for (auto i = m_adj[n->n].begin(); i != m_adj[n->n].end(); ++i, ++cntr)
            {
                auto count = false;
            
                for (auto it = visited.begin(); it != visited.end() && count == false; ++it)
                {
                    if (n->n == (*i)->a)
                        count = (*i)->b == (*it)->n ? true : false;
                    else
                        count = (*i)->a == (*it)->n ? true : false;
                }
            
				if (count == false && (*i)->load < (*i)->max_load)
                {
                    auto v = (*i)->a == n->n ? (*i)->b : (*i)->a;
                    to_visit.push(new node(v, visited.back()));
                }
				else if (count == false && (*i)->load == (*i)->max_load)
				{
					return vector<node*>();
				}
            }
        }
    }
    return vector<node*>();
}

bool operator<(const pair<node*, size_t>& lhs, const pair<node*, size_t>& rhs)
{
	if (lhs.second < rhs.second)
		return true;
	return false;
}

vector<node*> graph::sdp(char from, char to)
{
	priority_queue<pair<node*, size_t>, vector<pair<node*, size_t>>> to_visit;
    vector<node*> visited;
    
    to_visit.push(make_pair(new node(from, nullptr), 0));

    while (!to_visit.empty())
    {
        auto n = to_visit.top();
		visited.push_back(n.first);
        to_visit.pop();
        
		if (n.first->n == to)
        {
            return visited;
        }
        else
        {
			for (auto i = m_adj[n.first->n].begin(); i != m_adj[n.first->n].end(); ++i)
            {
                auto count = false;
            
                for (auto it = visited.begin(); it != visited.end() && count == false; ++it)
                {
					if (n.first->n == (*i)->a)
                        count = (*i)->b == (*it)->n ? true : false;
                    else
                        count = (*i)->a == (*it)->n ? true : false;
                }
            
				if (count == false && (*i)->load < (*i)->max_load)
                {
                    auto v = (*i)->a == n.first->n ? (*i)->b : (*i)->a;
					to_visit.push(make_pair(new node(v, visited.back()), n.second + (*i)->weight));
                }
				else if (count == false && (*i)->load == (*i)->max_load)
				{
					return vector<node*>();
				}
            }
        }
    }
    return vector<node*>();
}

vector<node*> graph::llp(char from, char to)
{
	priority_queue<pair<node*, size_t>, vector<pair<node*, size_t>>> to_visit;
	vector<node*> visited;

	to_visit.push(make_pair(new node(from, nullptr), 0));

	 while (!to_visit.empty())
    {
        auto n = to_visit.top();
		visited.push_back(n.first);
        to_visit.pop();
        
		if (n.first->n == to)
        {
            return visited;
        }
        else
        {
			for (auto i = m_adj[n.first->n].begin(); i != m_adj[n.first->n].end(); ++i)
            {
                auto count = false;
            
                for (auto it = visited.begin(); it != visited.end() && count == false; ++it)
                {
					if (n.first->n == (*i)->a)
                        count = (*i)->b == (*it)->n ? true : false;
                    else
                        count = (*i)->a == (*it)->n ? true : false;
                }
            
				if (count == false && (*i)->load < (*i)->max_load)
                {
                    auto v = (*i)->a == n.first->n ? (*i)->b : (*i)->a;
					to_visit.push(make_pair(new node(v, visited.back()), static_cast<size_t>(pow(10, 6) * (*i)->load / (*i)->max_load)));
                }
				else if (count == false && (*i)->load == (*i)->max_load)
				{
					return vector<node*>();
				}
            }
        }
    }

	return vector<node*>();
}

stack<node*> graph::sanitise(const vector<node*>& n) const
{
	stack<node*> stk;
	set<node*> temp;
	for (auto i = n.back(); i->p != nullptr; i = i->p)
	{
		stk.push(i);
		temp.insert(i);
	}

	for (auto i = n.begin(); i != n.end(); ++i)
	{
		if (temp.find(*i) == temp.end())
			delete *i;
	}

	return stk;
}

pair<size_t, size_t> graph::establish_connection(const size_t& time, const vector<node*>& n)
{
	auto s = sanitise(n);

	size_t hops = s.size();
	size_t prop = 0;

	while (!s.empty())
	{
		for (auto it = m_adj[s.top()->n].begin(); it != m_adj[s.top()->n].end(); ++it)
		{
			if ((s.top()->n == (*it)->a && s.top()->p->n == (*it)->b) || (s.top()->n == (*it)->b && s.top()->p->n == (*it)->a))
			{
				prop += (*it)->weight;
				++(*it)->load;
				m_connection[time].push_back(*it);
				break;
			}
		}

		delete s.top();
		s.pop();
	}

	return make_pair(hops, prop);
}

inline void graph::abolish_connection(const size_t& time)
{
	for (auto  it = m_connection[time].begin(); it != m_connection[time].end(); ++it)
	{
		++(*it)->load;
	}

	m_connection.erase(time);
}

template <typename T>
double average(const T& container)
{
	size_t sum = 0;
	for (auto it = container.cbegin(); it != container.cend(); ++it)
	{
		sum += *it;
	}

	return static_cast<double>(sum) / static_cast<double>(container.size());
}

size_t static_pow(size_t n, size_t p)
{
	return p == 1 ? n : n * static_pow(n, p - 1);
}

int main(int argc, char* argv[])
{
    string type(argv[1]);
    string topology(argv[2]);
    string work(argv[3]);

//    cout << type << " " << topology << " " << work << endl;

    ifstream i(topology, ios::in);
    ifstream workload(work, ios::in);
    graph g(i);

	map<size_t, tuple<char, char, size_t>> connection_data;

	size_t max_time = 0;

	while (!workload.eof())
	{
		tuple<char, char, size_t> listing;
		double start_time;
		double end_time;

		workload >> start_time;
		workload.get();
		workload >> get<0>(listing);
		workload.get();
		workload >> get<1>(listing);
		workload.get();
		workload >> end_time;

		get<2>(listing) = static_cast<size_t>((start_time + end_time) * static_pow(10, 6));
		connection_data.insert(make_pair(static_cast<size_t>(start_time * static_pow(10, 6)), listing));

		if (max_time < get<2>(listing))
			max_time = get<2>(listing);
	}

	
	size_t size = connection_data.size();
	size_t success_requests = 0;
	size_t blocked_requests = 0;
	vector<size_t> hops;
	vector<size_t> prop_delay;

	for (size_t time = 0; time < max_time; ++time)
	{
		auto it = connection_data.find(time);
		if (it != connection_data.end())
		{
			vector<node*> request;
			
			if (type == "SHP")
				request = g.shp(get<0>(it->second), get<1>(it->second));
			else if (type == "SDP")
				request = g.sdp(get<0>(it->second), get<1>(it->second));
			else
				request = g.llp(get<0>(it->second), get<1>(it->second));
			
			if (!request.empty())
			{
				auto data = g.establish_connection(get<2>(it->second), request);
				hops.push_back(data.first);
				prop_delay.push_back(data.second);
				++success_requests;
			}
			else
			{
				++blocked_requests;
			}

			g.abolish_connection(time);
		}
	}

	cout << fixed << showpoint << setprecision(2);
	cout << "total number of virtual circuit requests: " << size << endl;
	cout << "number of successfully routed requests: " << success_requests << endl;
	cout << "percentage of successfully routed request: "  << static_cast<double>(success_requests) / static_cast<double>(size) * 100.00 << endl;
	cout << "number of blocked requests: " << blocked_requests << endl;
	cout << "percentage of blocked requests: " << static_cast<double>(blocked_requests) / static_cast<double>(size) * 100.00 << endl;
	cout << "average number of hops per circuit: " << average(hops) << endl;
	cout << "average cumulative propagation delay per circuit: " << average(prop_delay) << endl;
    return 0;
}
