#include <iostream>
#include <map>
#include <vector>

using namespace std;

void acyclic_check_dps(vector<vector<int>>& graph, int x, int& result, map<int, int>& explored)
{
	if (result == 0)
	{
		explored[x]++;

		if (explored[x] > 1)
			result = 1;

		for (int value : graph[x])
		{
			acyclic_check_dps(graph, value, result, explored);
		}

		explored[x]--;
	}
}

int acyclic(vector<vector<int>>& graph)
{
	int result = 0;
	map<int, int> explored;

	for (size_t i = 0; i < graph.size(); i++)
	{
		if (!explored[i])
		{
			acyclic_check_dps(graph, i, result, explored);
		}
	}

	return result;
}

int main()
{
	size_t n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n, vector<int>());

	for (size_t i = 0; i < m; i++)
	{
		int x, y;
		std::cin >> x >> y;
		graph[x - 1].push_back(y - 1);
	}
	cout << acyclic(graph);
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.