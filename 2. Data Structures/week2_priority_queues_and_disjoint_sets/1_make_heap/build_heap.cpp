#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder
{
private:
	vector<int> data_;
	vector<pair<int, int>> swaps_;

	void WriteResponse() const
	{
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i)
		{
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}
	}

	void ReadData()
	{
		int n;
		cin >> n;
		data_.resize(n);
		for (int i = 0; i < n; ++i)
			cin >> data_[i];
	}

	void SiftDown(int Index)
	{
		while (Index < data_.size() && Index >= 0)
		{
			int MaxIndex = Index;

			int l = (2 * Index) + 1;
			if (l < data_.size() && data_[l] < data_[MaxIndex])
				MaxIndex = l;

			int r = (2 * Index) + 2;
			if (r < data_.size() && data_[r] < data_[MaxIndex])
				MaxIndex = r;

			if (Index != MaxIndex)
			{
				swap(data_[Index], data_[MaxIndex]);
				swaps_.push_back(make_pair(Index, MaxIndex));

				Index = MaxIndex;
			}
			else
			{
				Index = -1;
			}
		}
	}

	void GenerateSwaps()
	{
		swaps_.clear();

		for (int i = (data_.size() / 2) - 1; i >= 0; i--)
		{
			SiftDown(i);
		}
	}

public:
	void Solve()
	{
		ReadData();
		GenerateSwaps();
		WriteResponse();
	}
};

int main()
{
	ios_base::sync_with_stdio(false);

	HeapBuilder heap_builder;
	heap_builder.Solve();
	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.