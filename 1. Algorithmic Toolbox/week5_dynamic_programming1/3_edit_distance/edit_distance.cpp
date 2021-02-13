#include <iostream>
#include <string>
#include <vector>

using std::string;
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

int edit_distance(string& str1, string& str2)
{
	int x = str1.size() + 1, y = str2.size() + 1;
	vector<vector<int>> D(x, vector<int>(y, -1));
	for (size_t i = 0;i < x;i++)
	{
		D[i][0] = i;
	}
	for (size_t j = 1;j < y;j++)
	{
		D[0][j] = j;
	}

	for (size_t i = 1; i < x; i++)
	{
		for (size_t j = 1; j < y; j++)
		{
			int a = D[i][j - 1] + 1;
			int b = D[i - 1][j] + 1;
			int c;
			if (str1[i - 1] != str2[j - 1])
				c = D[i - 1][j - 1] + 1;
			else
				c = D[i - 1][j - 1];

			D[i][j] = minFromThree(a, b, c);
		}
	}

	return D[str1.size()][str2.size()];
}

int main()
{
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.