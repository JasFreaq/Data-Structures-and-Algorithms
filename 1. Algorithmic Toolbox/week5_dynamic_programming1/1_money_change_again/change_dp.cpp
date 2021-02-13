#include <iostream>
#include <vector>

using std::vector;

int minFromThree(int a, int b, int c)
{
	if (a < b)
	{
		if (a < c)
		{
			return a;
		}
		else
		{
			return c;
		}
	}
	else
	{
		if (b < c)
		{
			return b;
		}
		else
		{
			return c;
		}
	}
}

int get_change(int m)
{
	vector<size_t> arr = { 0,1,2,1,1 };
	for (size_t i = 5; i <= m; i++)
	{
		int a = arr[i - 4] + 1;
		int	b = arr[i - 3] + 1;
		int c = arr[i - 1] + 1;

		arr.push_back(minFromThree(a, b, c));
	}
	
	return arr[m];
}

int main()
{
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.