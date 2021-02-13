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

int lcs2(vector<int>& a, vector<int>& b)
{
	int n = a.size(), m = b.size();
	vector<vector<int>> D(n + 1, vector<int>(m + 1, 0));
		
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= m; j++)
		{
			int x = D[i][j - 1];
			int y = D[i - 1][j];
			int z = D[i - 1][j - 1];
			
			if (a[i - 1] == b[j - 1])
			{
				z++;
			}			
			
			D[i][j] = maxFromThree(x, y, z);
		}
	}

	return D[n][m];
}

int main()
{
	size_t n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	size_t m;
	std::cin >> m;
	vector<int> b(m);
	for (size_t i = 0; i < m; i++) {
		std::cin >> b[i];
	}

	std::cout << lcs2(a, b) << std::endl;
}
