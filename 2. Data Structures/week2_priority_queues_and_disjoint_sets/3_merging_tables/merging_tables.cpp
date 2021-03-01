#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement
{
	int size, parent, rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
		size(size), parent(parent), rank(rank) {}
};

struct DisjointSets
{
	int size;
	int max_table_size;
	vector<DisjointSetsElement> sets;

	DisjointSets(int size) : size(size), max_table_size(0), sets(size) {}

	int getParent(int table)
	{
		DisjointSetsElement* iterator = &sets[table];
		int parentIndex = table;
		vector<DisjointSetsElement*> commonSets;

		while (iterator->parent != -1)
		{
			parentIndex = iterator->parent;
			iterator = &sets[parentIndex];
			if (iterator->parent != -1)
			{
				commonSets.push_back(iterator);
			}
		}

		for (auto set : commonSets)
		{
			set->parent = parentIndex;
		}

		return parentIndex;
	}

	void CopyData(int realDestination, int realSource)
	{
		sets[realDestination].parent = realSource;
		sets[realSource].size += sets[realDestination].size;
		sets[realDestination].size = 0;
		max_table_size = max(max_table_size, sets[realSource].size);
	}

	void merge(int destination, int source)
	{
		int realDestination = getParent(destination);
		int realSource = getParent(source);

		if (realDestination != realSource)
		{
			if (sets[realSource].rank > sets[realDestination].rank)
			{
				CopyData(realDestination, realSource);
			}
			else
			{
				CopyData(realSource, realDestination);

				if (sets[realSource].rank == sets[realDestination].rank)
				{
					sets[realDestination].rank = sets[realDestination].rank + 1;
				}
			}
		}
	}
};

int main()
{
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto& table : tables.sets)
	{
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	vector<int> maximums;
	for (int i = 0; i < m; i++)
	{
		int destination, source;
		cin >> destination >> source;
		--destination;
		--source;

		tables.merge(destination, source);
		maximums.push_back(tables.max_table_size);
	}

	for (int i = 0; i < m; i++)
	{
		cout << maximums[i] << endl;
	}

	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.