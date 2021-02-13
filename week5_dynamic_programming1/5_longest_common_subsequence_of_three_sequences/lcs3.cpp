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

	/*if (a[0] == b[0] && b[0] == c[0])
		D[0][0][0] = 1;

	for (size_t i = 1; i < n; i++)
	{
		if (a[i] == b[0] && b[0] == c[0])
			D[i][0][0] = 1;
		else
			D[i][0][0] = D[i - 1][0][0];
	}
	for (size_t j = 1;j < m; j++)
	{
		if (a[0] == b[j] && b[j] == c[0])
			D[0][j][0] = 1;
		else
			D[0][j][0] = D[0][j - 1][0];
	}
	for (size_t k = 1;k < l; k++)
	{
		if (a[0] == b[0] && b[0] == c[k])
			D[0][0][k] = 1;
		else
			D[0][0][k] = D[0][0][k - 1];
	}

	for (size_t i = 1; i < n; i++)
	{
		for (size_t j = 1; j < m; j++)
		{
			if (a[i] == b[j] && b[j] == c[0])
			{
				D[i][j][0] = D[i - 1][j - 1][0] + 1;
			}
			else
			{
				int x = D[i][j - 1][0];
				int y = D[i - 1][j][0];

				D[i][j][0] = x > y ? x : y;
			}
		}
	}
	for (size_t i = 1; i < n; i++)
	{
		for (size_t k = 1; k < l; k++)
		{
			if (a[i] == b[0] && b[0] == c[k])
			{
				D[i][0][k] = D[i - 1][0][k - 1] + 1;
			}
			else
			{
				int x = D[i][0][k - 1];
				int y = D[i - 1][0][k];

				D[i][0][k] = x > y ? x : y;
			}
		}
	}
	for (size_t j = 1; j < m; j++)
	{
		for (size_t k = 1; k < l; k++)
		{
			if (a[0] == b[j] && b[j] == c[k])
			{
				D[0][j][k] = D[0][j - 1][k - 1] + 1;
			}
			else
			{
				int x = D[0][j][k - 1];
				int y = D[0][j - 1][k];

				D[0][j][k] = x > y ? x : y;
			}
		}
	}

	for (size_t i = 1; i < n; i++)
	{
		for (size_t j = 1; j < m; j++)
		{
			for (size_t k = 1; k < l; k++)
			{
				if (a[i] == b[j] && b[j] == c[k])
				{
					D[i][j][k] = D[i - 1][j - 1][k - 1] + 1;
				}
				else
				{
					int x1 = D[i - 1][j][k];
					int y1 = D[i][j - 1][k];
					int z1 = D[i][j][k - 1];
					int x2 = D[i][j - 1][k - 1];
					int y2 = D[i - 1][j][k - 1];
					int z2 = D[i - 1][j - 1][k];

					int x = maxFromThree(x1, y1, z1);
					int y = maxFromThree(x2, y2, z2);

					D[i][j][k] = x > y ? x : y;
				}
			}
		}
	}*/

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
