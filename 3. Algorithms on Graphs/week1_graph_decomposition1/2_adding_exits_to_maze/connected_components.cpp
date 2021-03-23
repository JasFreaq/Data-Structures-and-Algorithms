#include <iostream>
#include <vector>
#include <map>

using namespace std;

void depth_first_search(vector<vector<int>>& graph, int x, map<int, bool>& explored)
{
	explored[x] = true;

	for (int value : graph[x])
	{
		if (!explored[value])
			depth_first_search(graph, value, explored);
	}
}

int number_of_components(vector<vector<int>>& graph)
{
	int res = 0;
	map<int, bool> explored;

	for (size_t i = 0; i < graph.size(); i++)
	{
		if (!explored[i])
		{
			res++;
			depth_first_search(graph, i, explored);
		}
	}

	return res;
}

int main()
{
	size_t n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n, vector<int>());

	for (size_t i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		graph[x - 1].push_back(y - 1);
		graph[y - 1].push_back(x - 1);
	}
	cout << number_of_components(graph);
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.