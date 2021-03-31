#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int negative_cycle(vector<vector<int>>& graph, vector<vector<int>>& costs)
{
	vector<int> root(graph.size(), -1);
	vector<int> rootCost(graph.size(), 0);
	for (size_t i = 0; i < graph.size(); i++)
	{
		root[i] = i;
	}
	graph.push_back(root);
	costs.push_back(rootCost);

	vector<long long> distances(graph.size(), -1);
	distances[graph.size() - 1] = 0;
	bool relaxed;

	for (size_t count = 0; count < graph.size(); count++)
	{
		relaxed = false;
		for (size_t i = 0; i < graph.size(); i++)
		{
			for (size_t j = 0; j < graph[i].size(); j++)
			{
				size_t v = graph[i][j];
				if (distances[i] != -1 && (distances[v] > distances[i] + costs[i][j] || distances[v] == -1))
				{
					distances[v] = distances[i] + costs[i][j];
					relaxed = true;
				}
			}
		}

		if (!relaxed)
			break;
	}

	return relaxed;
}

int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n, vector<int>());
	vector<vector<int>> cost(n, vector<int>());
	for (int i = 0; i < m; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		graph[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	cout << negative_cycle(graph, cost);
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.