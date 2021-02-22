#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

class StackWithMax
{
	int max = -1;
	vector<int> stack, ordered_max_values;

public:

	void Push(int value)
	{
		stack.push_back(value);

		if (value >= max)
		{
			max = value;
			ordered_max_values.push_back(max);
		}
	}

	void Pop()
	{
		assert(stack.size());

		int back_value = stack.back();
		if (back_value == ordered_max_values.back())
		{
			ordered_max_values.pop_back();
		}

		stack.pop_back();
	}

	int Max() const
	{
		assert(stack.size());

		return ordered_max_values.back();
	}
};

int main()
{
	int num_queries = 0;
	cin >> num_queries;

	string query;
	string value;

	StackWithMax stack;
	vector<int> max_values;

	for (int i = 0; i < num_queries; ++i)
	{
		cin >> query;
		if (query == "push")
		{
			cin >> value;
			stack.Push(stoi(value));
		}
		else if (query == "pop")
		{
			stack.Pop();
		}
		else if (query == "max")
		{
			max_values.push_back(stack.Max());
		}
		else
		{
			assert(0);
		}
	}

	for (int i : max_values)
	{
		cout << i << "\n";
	}

	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.