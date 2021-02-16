#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace  std;

int partition3(vector<int>& A, int n)
{
	if (n < 3)
		return 0;

	int sum = 0;
	for (size_t i = 0; i < n; ++i)
	{
		sum += A[i];
	}
	if (sum % 3 != 0)
		return 0;

	int val = sum / 3;
	for (int a = 0; a < 3; a++)
	{
		n = A.size();
		vector<int> indices;
		int count = pow(2, n);

		for (int i = 0; i < count; i++)
		{
			sum = 0;
			vector<int> subIndices;
			for (int j = 0; j < n; j++)
			{
				if (A[j] == 0)
					continue;

				if ((i & (1 << j)) != 0)
				{
					sum += A[j];
					subIndices.push_back(j);
				}
			}

			if (sum == val)
			{
				indices = subIndices;
				break;
			}
		}

		if (indices.empty())
			return 0;

		for (int indice : indices)
		{
			A[indice] = 0;
		}
	}

	return 1;
}

int main()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (size_t i = 0; i < A.size(); ++i)
	{
		cin >> A[i];
	}
	unsigned num = chrono::system_clock::now().time_since_epoch().count();
	shuffle(A.begin(), A.end(), default_random_engine(num));
	cout << partition3(A, n) << '\n';
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.