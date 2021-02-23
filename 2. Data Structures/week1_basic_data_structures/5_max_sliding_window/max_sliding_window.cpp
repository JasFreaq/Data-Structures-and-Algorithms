#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

void max_sliding_window(vector<int> const& A, int w)
{
	deque<const int*> window;

	for (size_t i = 0, j = 0; i < A.size(); i++)
	{
		if (!window.empty())
		{
			for (size_t k = 0, n = window.size(); k < n; k++)
			{
				int val = *window.back();
				if (val <= A[i])
				{
					window.pop_back();
				}
				else
					break;
			}
		}
		window.push_back(&A[i]);

		if (i == w - 1)
		{
			std::cout << *window.front() << " ";
		}
		else if (i >= w)
		{
			if (window.front() == &A[j])
			{
				window.pop_front();
			}
			j++;

			std::cout << *window.front() << " ";
		}
	}

	return;
}


int main()
{
	int n = 0;
	cin >> n;

	vector<int> A(n);
	for (size_t i = 0; i < n; ++i)
		cin >> A.at(i);

	int w = 0;
	cin >> w;

	max_sliding_window(A, w);

	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.