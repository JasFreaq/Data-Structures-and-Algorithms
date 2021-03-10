#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef long long ll;

struct Answer
{
	size_t i, j, len;
};

class SubstringHash
{
	string s;
	size_t m_1 = 1000000007, m_2 = 1000000009;
	ll x_1 = 31, x_2 = 107;
	vector<ll> hashes_1, hashes_2, x1_raised = vector<ll>(1, 1), x2_raised = vector<ll>(1, 1);

public:
	SubstringHash(string s) : s(s)
	{
		hashes_1 = vector<ll>(s.size() + 1);
		hashes_2 = vector<ll>(s.size() + 1);

		for (size_t i = 1; i <= s.size(); i++)
		{
			ll hash_temp = (x_1 * hashes_1[i - 1] + s[i - 1]) % m_1;
			hash_temp += m_1;
			hash_temp %= m_1;
			hashes_1[i] = hash_temp;

			hash_temp = (x_2 * hashes_2[i - 1] + s[i - 1]) % m_2;
			hash_temp += m_2;
			hash_temp %= m_2;
			hashes_2[i] = hash_temp;
		}
	}

	pair<ll, ll> evaluate(int index, size_t len)
	{
		size_t n = x1_raised.size();
		if (len > n - 1)
		{
			for (size_t i = n; i <= len; i++)
			{
				ll x_temp = (x1_raised[i - 1] * (x_1 % m_1)) % m_1;
				x1_raised.push_back(x_temp % m_1);

				x_temp = (x2_raised[i - 1] * (x_2 % m_2)) % m_2;
				x2_raised.push_back(x_temp % m_2);
			}
		}

		ll value_1 = hashes_1[index + len] - x1_raised[len] * hashes_1[index] % m_1;
		value_1 += m_1;
		value_1 %= m_1;

		ll value_2 = hashes_2[index + len] - x2_raised[len] * hashes_2[index] % m_2;
		value_2 += m_2;
		value_2 %= m_2;

		return pair<ll, ll>(value_1, value_2);
	}
};

vector<pair<ll, ll>> compute_hash_table(SubstringHash& substring_hash, size_t len, size_t strlen)
{
	vector<pair<ll, ll>> hash_tables(strlen - len + 1);
	for (size_t i = 0, n = hash_tables.size(); i < n; i++)
	{
		hash_tables[i] = substring_hash.evaluate(i, len);
	}

	return hash_tables;
}

bool check_for_len(SubstringHash& a_hash, SubstringHash& b_hash, Answer& ans, size_t len, size_t a_len, size_t b_len)
{
	map<pair<ll, ll>, size_t> smaller_string_dict;
	if (a_len < b_len)
	{
		for (size_t i = 0, n = a_len - len + 1; i < n; i++)
		{
			smaller_string_dict[a_hash.evaluate(i, len)] = i + 1;
		}

		size_t n = b_len - len + 1;
		for (size_t i = 0; i < n; i++)
		{
			size_t val = smaller_string_dict[b_hash.evaluate(i, len)];
			if (val)
			{
				ans = { val - 1, i, len };
				return true;
			}
		}

		return false;
	}
	else
	{
		for (size_t i = 0, n = b_len - len + 1; i < n; i++)
		{
			smaller_string_dict[b_hash.evaluate(i, len)] = i + 1;
		}

		size_t n = a_len - len + 1;
		for (size_t i = 0; i < n; i++)
		{
			size_t val = smaller_string_dict[a_hash.evaluate(i, len)];
			if (val)
			{
				ans = { i, val - 1, len };
				return true;
			}
		}

		return false;
	}
}

Answer solve(const string& s, const string& t)
{
	size_t l = 1, r = s.size() < t.size() ? s.size() : t.size();

	SubstringHash s_hash(s), t_hash(t);
	Answer ans = { 0, 0, 0 };

	while (l <= r)
	{
		size_t check_len = l + (r - l) / 2;
		if (check_for_len(s_hash, t_hash, ans, check_len, s.size(), t.size()))
		{
			l = check_len + 1;
		}
		else
		{
			r = check_len - 1;
		}
	}

	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);

	string s, t;
	while (cin >> s >> t)
	{
		Answer ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.