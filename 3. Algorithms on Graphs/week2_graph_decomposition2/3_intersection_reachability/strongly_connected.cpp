#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

struct node
{
	int value = -1, preorder = -1, postorder = -1;
};

class SCCSolver
{
	vector<vector<int>> reverse_graph(const vector<vector<int>>& graph)
	{
		vector<vector<int>> temp_graph(graph.size());
		for (size_t i = 0; i < graph.size(); i++)
		{
			for (size_t j = 0; j < graph[i].size(); j++)
			{
				temp_graph[graph[i][j]].push_back(i);
			}
		}
		return temp_graph;
	}

public:
	void dfs(vector<vector<int>>& graph, int x, vector<int>& visited, stack<int>& Stack)
	{
		visited[x] = 1;

		for (int i = 0; i < graph[x].size(); i++)
		{
			if (!visited[graph[x][i]]) {
				visited[graph[x][i]] = 1;
				dfs(graph, graph[x][i], visited, Stack);
			}
		}

		Stack.push(x);
	}

	int solve(vector<vector<int> > adj)
	{
		int result = 0;
		stack<int> Stack;

		vector<int> visited(adj.size(), 0);

		for (int i = 0; i < adj.size(); i++)
		{
			if (!visited[i]) {
				dfs(adj, i, visited, Stack);
			}
		}

		vector<vector<int>> rev_graph = reverse_graph(adj);

		for (int i = 0; i < adj.size(); i++)
		{
			visited[i] = 0;
		}

		while (!Stack.empty())
		{
			int x = Stack.top();
			Stack.pop();

			if (!visited[x])
			{
				stack<int> componentStack;
				dfs(rev_graph, x, visited, componentStack);
				result++;
			}
		}
		return result;
	}
};


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
	}

	SCCSolver s;
	cout << s.solve(graph);
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Mosc