#include <iostream>
#include <vector>
#include <algorithm>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders
{
	int n;
	vector <int> key;
	vector <int> left;
	vector <int> right;

public:
	void read()
	{
		cin >> n;
		key.resize(n);
		left.resize(n);
		right.resize(n);
		for (int i = 0; i < n; i++)
		{
			cin >> key[i] >> left[i] >> right[i];
		}
	}


	void in_order(vector<int>& result, int node_index = 0)
	{
		if (!node_index)
			result = vector<int>();

		if (left[node_index] > 0)
			in_order(result, left[node_index]);
		result.push_back(key[node_index]);
		if (right[node_index] > 0)
			in_order(result, right[node_index]);
	}

	void pre_order(vector<int>& result, int node_index = 0)
	{
		if (!node_index)
			result = vector<int>();

		result.push_back(key[node_index]);
		if (left[node_index] > 0)
			pre_order(result, left[node_index]);
		if (right[node_index] > 0)
			pre_order(result, right[node_index]);
	}

	void post_order(vector<int>& result, int node_index = 0)
	{
		if (!node_index)
			result = vector<int>();

		if (left[node_index] > 0)
			post_order(result, left[node_index]);
		if (right[node_index] > 0)
			post_order(result, right[node_index]);
		result.push_back(key[node_index]);
	}
};

void print(vector <int> a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		if (i > 0)
		{
			cout << ' ';
		}
		cout << a[i];
	}
	cout << '\n';
}

int main_with_large_stack_space()
{
	ios_base::sync_with_stdio(0);

	TreeOrders t;
	t.read();
	vector<int> result;

	t.in_order(result);
	print(result);
	t.pre_order(result);
	print(result);
	t.post_order(result);
	print(result);

	return 0;
}

int main(int argc, char** argv)
{
#if defined(__unix__) || defined(__APPLE__)
	const rlim_t kStackSize = 16 * 1024 * 1024;
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
				std::cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}
#endif

	return main_with_large_stack_space();
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.