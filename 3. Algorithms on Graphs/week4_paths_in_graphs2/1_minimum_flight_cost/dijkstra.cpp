#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

#define LLONG_MAX std::numeric_limits<long long>::max()

struct cost
{
	int index = -1;
	int value = -1;

	cost(int Index, int Value) : index(Index), value(Value) { }
};

struct compare
{
	bool operator()(cost const& c1, cost const& c2)
	{
		return c1.value > c2.value;
	}
};

long long distance(vector<vector<int>>& graph, vector<vector<int>>& costs, int s, int t)
{
	vector<long long> distances(graph.size(), LLONG_MAX);
	distances[s] = 0;
	priority_queue<cost, vector<cost>, compare> min_heap;
	min_heap.push(*(new cost(s, 0)));

	for (size_t i = 0; i < graph.size() - 1; i++)
	{
		for (size_t j = 0; j < costs[i].size(); j++)
		{
			cost c(graph[i][j], costs[i][j]);
			min_heap.push(c);
		}

		while (!min_heap.empty())
		{
			size_t u = min_heap.top().index;
			min_heap.pop();

			for (size_t j = 0; j < graph[u].size(); j++)
			{
				size_t v = graph[u][j];
				if (distances[u] != LLONG_MAX && distances[v] > distances[u] + costs[u][j])
				{
					distances[v] = distances[u] + costs[u][j];
					min_heap.push(*(new cost(v, distances[v])));
				}
			}
		}
	}

	if (distances[t] != LLONG_MAX)
		return distances[t];

	return -1;
}

int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n, vector<int>());
	vector<vector<int>> costs(n, vector<int>());
	for (int i = 0; i < m; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		graph[x - 1].push_back(y - 1);
		costs[x - 1].push_back(w);
	}

	int s, t;
	cin >> s >> t;
	s--, t--;
	cout << distance(graph, costs, s, t);
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.