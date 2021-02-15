#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int>& Weights)
{
	int n = Weights.size();
	vector<vector<int>> V(n + 1, vector<int>(W + 1, 0));

	for (size_t w = 1; w <= W; w++)
	{
		for (size_t i = 1; i <= n; i++)
		{
			V[i][w] = V[i - 1][w];
			if (Weights[i - 1] <= w)
			{
				int val = V[i - 1][w - Weights[i - 1]] + Weights[i - 1];
				if (V[i][w] < val)
					V[i][w] = val;
			}
		}
	}

	return V[n][W];
}

int main()
{
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++)
	{
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';
}
