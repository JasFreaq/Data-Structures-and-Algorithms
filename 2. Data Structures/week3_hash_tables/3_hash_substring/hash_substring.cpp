#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

struct Data
{
	string pattern, text;
};

bool are_equal(const string& a, size_t a_beg, const string& b)
{
	for (int i = 0, n = b.size(); i < n; i++)
	{
		if (a[i + a_beg] != b[i])
			return false;
	}

	return true;
}

ull hash_func(const string& S, int beg, int end, size_t prime, size_t multiplier)
{
	unsigned long long hash = 0;
	for (int i = end; i >= beg; i--)
		hash = (hash * multiplier + S[i]) % prime;

	return hash;
}

vector<ull> precompute_hashes(const string& Text, size_t pattern_length, size_t prime, size_t x)
{
	vector<ull> hashes(Text.size() - pattern_length + 1);
	hashes[Text.size() - pattern_length] = hash_func(Text, Text.size() - pattern_length, Text.size() - 1, prime, x);
	ull y = 1;

	for (int i = 1; i <= pattern_length; i++)
	{
		y = (y * x) % prime;
	}

	for (int i = Text.size() - pattern_length - 1; i >= 0; --i)
	{
		long long preHash = x * hashes[i + 1] + Text[i] - y * Text[i + pattern_length];
		while (preHash < 0)
			preHash += prime;

		hashes[i] = preHash % prime;
	}

	return hashes;
}

Data read_input()
{
	Data data;
	cin >> data.pattern >> data.text;
	return data;
}

void print_occurrences(const vector<ull>& output)
{
	for (size_t i = 0; i < output.size(); i++)
		std::cout << output[i] << " ";

	cout << "\n";
}

vector<ull> get_occurrences(const Data& input)
{
	const string& s = input.pattern, t = input.text;
	vector<ull> ans;
	size_t prime = 1000000009;

	ull x = (rand() % (prime - 1)) + 1;

	ull pattern_hash = hash_func(s, 0, s.size() - 1, prime, x);
	vector<ull> hashes = precompute_hashes(t, s.size(), prime, x);

	for (int i = 0, n = t.size() - s.size(); i <= n; i++)
	{
		if (pattern_hash != hashes[i])
			continue;

		if (are_equal(t, i, s))
			ans.push_back(i);
	}

	return ans;
}


int main()
{
	ios_base::sync_with_stdio(false);

	print_occurrences(get_occurrences(read_input()));

	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.