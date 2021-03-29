#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int distance(vector<vector<int>>& graph, int s, int t)
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

	return distances[t];
}

int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		graph[x - 1].push_back(y - 1);
		graph[y - 1].push_back(x - 1);
	}

	int s, t;
	cin >> s >> t;
	s--, t--;
	cout << distance(graph, s, t);
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.