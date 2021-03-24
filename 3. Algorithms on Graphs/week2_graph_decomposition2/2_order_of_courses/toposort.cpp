#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct node
{
	int value = -1, preorder = -1, postorder = -1;
};

int compare(const void* a, const void* b)
{
	const node* x = (node*)a;
	const node* y = (node*)b;

	if (x->postorder > y->postorder)
		return -1;

	if (x->postorder < y->postorder)
		return 1;

	return 0;
}

class Toposort
{
	size_t clock = 0;
	vector<node> order;
	vector<vector<int>> graph;
	map<int, bool> explored;

public:
	void dfs(int x)
	{
		explored[x] = true;

		order[x].value = x;
		order[x].preorder = clock++;

		for (int value : graph[x])
		{
			if (!explored[value])
				dfs(value);
		}

		order[x].postorder = clock++;
	}

	vector<int> sort(vector<vector<int>> adj)
	{
		graph = adj;
		order = *(new vector<node>(graph.size()));
		vector<int> sources;

		for (size_t i = 0; i < graph.size(); i++)
		{
			if (!explored[i])
			{
				if (!graph[i].empty())
					dfs(i);
				else
					sources.push_back(i);
			}
		}

		for (size_t i = 0; i < sources.size(); i++)
		{
			if (!explored[sources[i]])
				dfs(sources[i]);
		}

		qsort(&order[0], graph.size(), sizeof(node), compare);

		vector<int> result;
		for (node n : order)
		{
			result.push_back(n.value);
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

	Toposort t;
	vector<int> order = t.sort(graph);
	for (size_t i = 0; i < order.size(); i++)
	{
		cout << order[i] + 1 << " ";
	}
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.