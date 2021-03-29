#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bipartite(vector<vector<int>>& graph)
{
	vector<int> colours(graph.size(), -1);
	queue<int> vertices_to_process;

	for (size_t i = 0; i < graph.size(); i++)
	{
		if (colours[i] == -1)
		{
			colours[i] = 0;
			vertices_to_process.push(i);

			while (!vertices_to_process.empty())
			{
				int u = vertices_to_process.front();
				vertices_to_process.pop();

				for (int v : graph[u])
				{
					if (colours[v] == -1)
					{
						vertices_to_process.push(v);
						colours[v] = colours[u] ? 0 : 1;
					}
					else if (colours[v] == colours[u])
						return 0;
				}
			}
		}
	}

	return 1;
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

	cout << bipartite(graph);
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.