#include <iostream>
#include <vector>

using std::vector;

int maxFromThree(int a, int b, int c)
{
	if (a > b)
	{
		if (a > c)
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
		if (b > c)
		{
			return b;
		}
		else
		{
			return c;
		}
	}
}

int lcs3(vector<int>& a, vector<int>& b, vector<int>& c)
{
	int n = a.size(), m = b.size(), l = c.size();
	vector<vector<vector<int>>> D(n + 1, vector<vector<int>>(m + 1, vector<int>(l + 1, 0)));

	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < m + 1; j++)
		{
			for (int k = 1; k < l + 1; k++)
			{
				if (a[i - 1] == b[j - 1] && a[i - 1] == c[k - 1])
				{
					int x = D[i - 1][j - 1][k - 1] + 1 > D[i][j - 1][k] ? D[i - 1][j - 1][k - 1] + 1 : D[i][j - 1][k];
					int y = D[i - 1][j][k] > D[i][j][k - 1] ? D[i - 1][j][k] : D[i][j][k - 1];

					D[i][j][k] = x > y ? x : y;
				}
				else
				{
					int x = D[i - 1][j - 1][k - 1] > D[i][j - 1][k] ? D[i - 1][j - 1][k - 1] : D[i][j - 1][k];
					int y = D[i - 1][j][k] > D[i][j][k - 1] ? D[i - 1][j][k] : D[i][j][k - 1];

					D[i][j][k] = x > y ? x : y;
				}
			}
		}
	}

	return D[n][m][l];
}

int main()
{
	size_t an;
	std::cin >> an;
	vector<int> a(an);
	for (size_t i = 0; i < an; i++)
	{
		std::cin >> a[i];
	}

	size_t bn;
	std::cin >> bn;
	vector<int> b(bn);
	for (size_t i = 0; i < bn; i++)
	{
		std::cin >> b[i];
	}

	size_t cn;
	std::cin >> cn;
	vector<int> c(cn);
	for (size_t i = 0; i < cn; i++)
	{
		std::cin >> c[i];
	}

	std::cout << lcs3(a, b, c) << std::endl;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.