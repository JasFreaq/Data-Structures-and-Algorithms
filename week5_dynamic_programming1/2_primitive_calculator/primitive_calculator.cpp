#include <iostream>
#include <vector>
#include <algorithm>

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

vector<int> optimal_sequence(int n)
{
	if (n == 1)
		return vector<int>{1};
	if (n == 2)
		return vector<int>{1, 2};
	if (n == 3)
		return vector<int>{1, 3};

	vector<int> arr = { 0,1,1 };
	for (size_t i = 3; i <= n; i++)
	{
		size_t val = i + 1;
		size_t a = INT32_MAX, b = INT32_MAX, c = arr[i - 1] + 1;
		if (val % 3 == 0)
		{
			a = arr[i / 3] + 1;
		}

		if (val % 2 == 0)
		{
			b = arr[i / 2] + 1;
		}

		arr.push_back(minFromThree(a, b, c));
	}

	std::vector<int> sequence;
	while (n >= 1)
	{
		sequence.push_back(n);
		int m = n - 1;
		size_t a = INT32_MAX, b = INT32_MAX, c = INT32_MAX;
		if (n % 3 == 0)
		{
			a = arr[m / 3];
		}

		if (n % 2 == 0)
		{
			b = arr[m / 2];
		}

		if (n > 1)
		{
			c = arr[m - 1];
		}

		if (a < b)
		{
			if (a < c)
			{
				n /= 3;
			}
			else
			{
				n--;
			}
		}
		else
		{
			if (b < c)
			{
				n /= 2;
			}
			else
			{
				n--;
			}
		}
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;
}

int main()
{
	int n;
	std::cin >> n;
	vector<int> sequence = optimal_sequence(n);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 0; i < sequence.size(); ++i)
	{
		std::cout << sequence[i] << " ";
	}
}
