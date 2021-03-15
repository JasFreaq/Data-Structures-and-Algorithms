#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef long long ll;

class SubstringHash
{
	string s;
	size_t m = 1000000007;
	ll x = 31;
	vector<ll> hashes, x_raised = vector<ll>(1, 1);

public:
	SubstringHash(string s) : s(s)
	{
		hashes = vector<ll>(s.size() + 1);

		for (size_t i = 1; i <= s.size(); i++)
		{
			ll hash_temp = (x * hashes[i - 1] + s[i - 1]) % m;
			hash_temp += m;
			hash_temp %= m;
			hashes[i] = hash_temp;
		}
	}

	void evaluate_x_powers(size_t len)
	{
		for (size_t i = 1; i <= len; i++)
		{
			ll x_temp = (x_raised[i - 1] * (x % m)) % m;
			x_raised.push_back(x_temp % m);
		}
	}

	ll evaluate(size_t i, size_t j)
	{
		size_t len = j - i + 1;

		ll value_1 = hashes[i + len] - x_raised[len] * hashes[i] % m;
		value_1 += m;
		value_1 %= m;

		return value_1;
	}
};

class Solver
{
	size_t k, mismatch_count = 0, iteration = 1;
	string t, p;
	SubstringHash text_hash, pattern_hash;
	map<ll, bool> valid_hashes, invalid_hashes;

public:

	Solver(int count, string text, string pattern) : k(count), mismatch_count(0), t(text), p(pattern), text_hash(text), pattern_hash(pattern)
	{
		text_hash.evaluate_x_powers(pattern.size());
		pattern_hash.evaluate_x_powers(pattern.size());
	}

	void find_mismatch(size_t index, size_t l, size_t r)
	{
		if (mismatch_count > k)
			return;

		if (l <= r)
		{
			size_t m = l + (r - l) / 2;
			if (t[index + m] != p[m])
			{
				mismatch_count++;
			}

			if (text_hash.evaluate(index, index + m - 1) != pattern_hash.evaluate(0, m - 1))
			{
				find_mismatch(index, l, m - 1);
			}

			if (text_hash.evaluate(index + m + 1, index + r) != pattern_hash.evaluate(m + 1, r))
			{
				find_mismatch(index, m + 1, r);
			}
		}
	}

	vector<int> solve()
	{
		vector<int> pos;
		size_t candidates_num = t.size() - p.size() + 1;

		for (size_t i = 0; i < candidates_num; i++)
		{
			ll current_substring_hash = text_hash.evaluate(i, i + p.size() - 1);
			if (!invalid_hashes[current_substring_hash])
			{
				if (valid_hashes[current_substring_hash])
				{
					pos.push_back(i);
				}
				else
				{
					mismatch_count = 0;
					find_mismatch(i, 0, p.size() - 1);
					if (mismatch_count <= k)
					{
						pos.push_back(i);
						valid_hashes[current_substring_hash] = true;
					}
					else
					{
						invalid_hashes[current_substring_hash] = true;
					}
				}
			}
		}

		return pos;
	}
};

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);

	size_t k;
	string t, p;
	while (cin >> k >> t >> p)
	{
		Solver s(k, t, p);
		vector<int> a = s.solve();
		cout << a.size();

		for (int x : a)
		{
			cout << " " << x;
		}
		cout << "\n";
	}
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.