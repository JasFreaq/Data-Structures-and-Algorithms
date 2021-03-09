#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class Solver
{
	string s;
	size_t m_1 = 1000000007, m_2 = 1000000009, len;
	ll x;
	vector<ll> hashes_1, hashes_2, x1_raised = vector<ll>(1, 1), x2_raised = vector<ll>(1, 1);

public:
	Solver(string s) : s(s)
	{
		x = 263;

		hashes_1 = vector<ll>(s.size() + 1);
		hashes_2 = vector<ll>(s.size() + 1);

		for (size_t i = 1; i <= s.size(); i++)
		{
			ll hash_temp = (x * hashes_1[i - 1] + s[i - 1]) % m_1;
			hash_temp += m_1;
			hash_temp %= m_1;
			hashes_1[i] = hash_temp;

			hash_temp = (x * hashes_2[i - 1] + s[i - 1]) % m_2;
			hash_temp += m_2;
			hash_temp %= m_2;
			hashes_2[i] = hash_temp;
		}
	}

	bool equivalent_hash(bool is_hash_one, int a, int b)
	{
		size_t n = x1_raised.size();
		if (len > n - 1)
		{
			for (size_t i = n; i <= len; i++)
			{
				ll x_temp = (x1_raised[i - 1] * (x % m_1)) % m_1;
				x1_raised.push_back(x_temp % m_1);

				x_temp = (x2_raised[i - 1] * (x % m_2)) % m_2;
				x2_raised.push_back(x_temp % m_2);
			}
		}

		if (is_hash_one)
		{
			long long value_1 = hashes_1[a + len] - x1_raised[len] * hashes_1[a] % m_1;
			value_1 += m_1;
			value_1 %= m_1;

			long long value_2 = hashes_1[b + len] - x1_raised[len] * hashes_1[b] % m_1;
			value_2 += m_1;
			value_2 %= m_1;

			return value_1 == value_2;
		}

		long long value_1 = hashes_2[a + len] - x2_raised[len] * hashes_2[a] % m_2;
		value_1 += m_2;
		value_1 %= m_2;

		long long value_2 = hashes_2[b + len] - x2_raised[len] * hashes_2[b] % m_2;
		value_2 += m_2;
		value_2 %= m_2;

		return value_1 == value_2;
	}

	bool ask(int a, int b, int l)
	{
		len = l;

		return equivalent_hash(true, a, b) && equivalent_hash(false, a, b);
	}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	vector<string> ans;

	for (int i = 0; i < q; i++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		ans.push_back(solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}

	for (int i = 0; i < q; i++)
	{
		cout << ans[i];
	}
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.