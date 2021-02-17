#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <vector>
#include <limits.h>

using std::vector;
using std::string;
using std::min;
using std::max;

bool comp(long long a, long long b)
{
	return (a < b);
}

long long eval(long long a, long long b, char op)
{
	if (op == '*')
	{
		return a * b;
	}
	else if (op == '+')
	{
		return a + b;
	}
	else if (op == '-')
	{
		return a - b;
	}
	else
	{
		assert(0);
	}
}

void min_and_max(vector<vector<long long>> minArr, vector<vector<long long>> MaxArr, const string& exp, int i, int j, long long& m, long long& M)
{
	m = LONG_MAX;
	M = LONG_MIN;

	for (int k = i; k <= j - 1; k++)
	{
		char opK = exp[(2 * k) - 1];

		long long a = eval(MaxArr[i][k], MaxArr[k + 1][j], opK);
		long long b = eval(MaxArr[i][k], minArr[k + 1][j], opK);
		long long c = eval(minArr[i][k], MaxArr[k + 1][j], opK);
		long long d = eval(minArr[i][k], minArr[k + 1][j], opK);

		m = std::min({ m, a, b, c, d }, comp);
		M = std::max({ M, a, b, c, d }, comp);
	}
}

long long get_maximum_value(const string& exp)
{
	int n = ((exp.size() - 1) / 2) + 1;
	vector<vector<long long>> minArr(n + 1, vector<long long>(n + 1, 0)), MaxArr(n + 1, vector<long long>(n + 1, 0));
	for (int i = 1; i <= n; i++)
	{
		minArr[i][i] = MaxArr[i][i] = static_cast<long long>(static_cast<int>(exp[2 * (i - 1)]) - 48);
	}

	for (int s = 1; s <= n - 1; s++)
	{
		for (int i = 1; i <= n - s; i++)
		{
			int j = i + s;
			long long m, M;

			min_and_max(minArr, MaxArr, exp, i, j, m, M);
			minArr[i][j] = m;
			MaxArr[i][j] = M;
		}
	}

	return MaxArr[1][n];
}

int main()
{
	string s;
	std::cin >> s;
	std::cout << get_maximum_value(s) << '\n';
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.