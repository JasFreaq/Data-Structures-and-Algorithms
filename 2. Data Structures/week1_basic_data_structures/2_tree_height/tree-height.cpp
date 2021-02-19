#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node
{
public:
	int key;
	Node* parent;
	vector<Node*> children;

	Node()
	{
		this->parent = NULL;
	}

	void setParent(Node* theParent)
	{
		parent = theParent;
		parent->children.push_back(this);
	}
};

int postOrder(Node* node, vector<int>& nodeHeights)
{
	if (node->children.size() == 0)
	{
		nodeHeights[node->key] = 1;
		return 0;
	}

	int max = 0;
	int n = node->children.size();

	for (int i = 0; i < n; i++)
	{
		int height;
		Node* v = node->children[i];
		if (nodeHeights[v->key] != 0)
		{
			height = 1 + nodeHeights[v->key];
		}
		else
		{
			height = 1 + postOrder(v, nodeHeights);
		}

		if (height > max)
			max = height;
	}

	nodeHeights[node->key] = max;
	return max;
}

int main_with_large_stack_space()
{
	ios_base::sync_with_stdio(0);

	int n, rootIndex;
	cin >> n;
	vector<Node> nodes(n);
	for (int child_index = 0; child_index < n; child_index++)
	{
		int parent_index;
		cin >> parent_index;
		if (parent_index >= 0)
		{
			nodes[child_index].setParent(&nodes[parent_index]);
		}
		else
		{
			rootIndex = child_index;
		}
		nodes[child_index].key = child_index;
	}

	vector<int> nodeHeights(n, 0);
	cout << postOrder(&nodes[rootIndex], nodeHeights) + 1 << endl;
	return 0;
}

int main(int argc, char** argv)
{

#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				cerr << "setrlimit returned result = " << result << endl;
			}
		}
	}

#endif

	main_with_large_stack_space();
	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.