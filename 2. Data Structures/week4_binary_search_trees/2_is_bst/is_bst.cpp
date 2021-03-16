#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node
{
	int key;
	int left;
	int right;

	Node() : key(0), left(-1), right(-1) {}
	Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order(const vector<Node>& tree, vector<int>& result, Node node)
{
	if (node.left > 0)
		in_order(tree, result, tree[node.left]);
	result.push_back(node.key);
	if (node.right > 0)
		in_order(tree, result, tree[node.right]);
}

bool IsBinarySearchTree(const vector<Node>& tree)
{
	if (tree.empty() || tree.size() == 1)
		return true;

	vector<int> elements_in_order;
	in_order(tree, elements_in_order, tree[0]);
	for (size_t i = 0, n = elements_in_order.size(); i < n; i++)
	{
		if (i == 0)
		{
			if (elements_in_order[0] > elements_in_order[1])
				return false;
		}
		else if (i == n - 1)
		{
			if (elements_in_order[n - 1] < elements_in_order[n - 2])
				return false;
		}
		else
		{
			if (elements_in_order[i - 1] > elements_in_order[i])
				return false;
			if (elements_in_order[i + 1] < elements_in_order[i])
				return false;
		}
	}

	return true;
}

int main()
{
	int nodes;
	cin >> nodes;
	vector<Node> tree;
	for (int i = 0; i < nodes; i++)
	{
		int key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}

	if (IsBinarySearchTree(tree))
	{
		cout << "CORRECT" << endl;
	}
	else
	{
		cout << "INCORRECT" << endl;
	}
	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.