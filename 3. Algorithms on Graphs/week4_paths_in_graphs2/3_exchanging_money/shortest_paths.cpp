#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

#define LLONG_MAX std::numeric_limits<long long>::max()

vector<int> bfs(vector<vector<int>>& graph, int s)
{
	vector<int> distances(graph.size(), -1);
	distances[s] = 0;

	queue<int> vertices_to_process;
	vertices_to_process.push(s);

	while (!vertices_to_process.empty())
	{
		int u = vertices_to_process.front();
		vertices_to_process.pop();

		for (int v : graph[u])
		{
			if (distances[v] == -1)
			{
				vertices_to_process.push(v);
				distances[v] = distances[u] + 1;
			}
		}
	}

	return distances;
}

void shortest_paths(vector<vector<int>>& graph, vector<vector<int>>& costs, int s, vector<long long>& distances, vector<int>& reachable, vector<int>& shortest)
{
	distances[s] = 0;
	vector<int> relaxed_on_last;

	for (size_t count = 0; count < graph.size(); count++)
	{
		for (size_t i = 0; i < graph.size(); i++)
		{
			for (size_t j = 0; j < graph[i].size(); j++)
			{
				size_t v = graph[i][j];
				if (distances[i] != LLONG_MAX && distances[v] > distances[i] + costs[i][j])
				{
					distances[v] = distances[i] + costs[i][j];

					if (count == graph.size() - 1)
						relaxed_on_last.push_back(v);
				}
			}
		}
	}

	for (size_t i = 0; i < graph.size(); i++)
	{
		if (distances[i] != LLONG_MAX)
		{
			reachable[i] = 1;
		}
	}

	for (int i : relaxed_on_last)
	{
		vector<int> negative_infinity = bfs(graph, i);
		for (size_t j = 0; j < negative_infinity.size(); j++)
		{
			if (negative_infinity[j] > -1)
				shortest[j] = 0;
		}
	}
}

int main()
{
	int n, m, s;
	std::cin >> n >> m;

	vector<vector<int>> graph(n, vector<int>());
	vector<vector<int>> cost(n, vector<int>());
	for (int i = 0; i < m; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		graph[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}

	cin >> s;
	s--;
	vector<long long> distance(n, LLONG_MAX);
	vector<int> reachable(n, 0);
	vector<int> shortest(n, 1);

	shortest_paths(graph, cost, s, distance, reachable, shortest);
	for (int i = 0; i < n; i++)
	{
		if (!reachable[i])
		{
			cout << "*\n";
		}
		else if (!shortest[i])
		{
			cout << "-\n";
		}
		else
		{
			cout << distance[i] << "\n";
		}
	}
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.