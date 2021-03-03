#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query
{
	string type, s;
	size_t ind;
};

class QueryProcessor
{
	int bucket_count;
	vector<vector<string>> elems;
	vector<string> output;

	size_t hash_func(const string& s) const
	{
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;

		for (int i = static_cast<int>(s.size()) - 1; i >= 0; i--)
			hash = (hash * multiplier + s[i]) % prime;

		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count)
	{
		elems = *(new vector<vector<string>>(bucket_count, vector<string>()));
	}

	Query readQuery() const
	{
		Query query;
		cin >> query.type;

		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;

		return query;
	}

	void writeSearchResult(bool was_found)
	{
		output.push_back(was_found ? "yes\n" : "no\n");
	}

	bool findValue(const string& val)
	{
		size_t hash_value = hash_func(val);
		vector<string> bucket = elems[hash_value];

		for (int i = static_cast<int>(bucket.size()) - 1; i >= 0; i--)
		{
			if (bucket[i] == val)
			{
				return true;
			}
		}

		return false;
	}

	bool findValue(const string& val, size_t& index)
	{
		size_t hash_value = hash_func(val);
		vector<string> bucket = elems[hash_value];

		for (int i = static_cast<int>(bucket.size()) - 1; i >= 0; i--)
		{
			if (bucket[i] == val)
			{
				index = i;
				return true;
			}
		}

		index = 0;
		return false;
	}

	void processQuery(const Query& query)
	{
		if (query.type == "check")
		{
			vector<string> bucket = elems[query.ind];

			for (int i = static_cast<int>(bucket.size()) - 1; i >= 0; i--)
			{
				output.push_back(bucket[i] + " ");
			}
			output.push_back("\n");
		}
		else
		{
			if (query.type == "find")
			{
				bool was_found = findValue(query.s);
				writeSearchResult(was_found);
			}
			else if (query.type == "add")
			{
				size_t hash_value = hash_func(query.s);
				vector<string> bucket = elems[hash_value];

				if (!findValue(query.s))
				{
					bucket.push_back(query.s);
					elems[hash_value] = bucket;
				}
			}
			else if (query.type == "del")
			{
				size_t hash_value = hash_func(query.s);
				vector<string> bucket = elems[hash_value];

				size_t i;
				if (findValue(query.s, i))
				{
					bucket.erase(bucket.begin() + i);
					elems[hash_value] = bucket;
				}
			}
		}
		//if (query.type == "check") 
		//{
		//	// use reverse order, because we append strings to the end
		//	for (int i = static_cast<int>(elems.size()) - 1; i >= 0; i--)
		//	{
		//		if (hash_func(elems[i]) == query.ind)
		//			cout << elems[i] << " ";
		//	}
		//	cout << "\n";
		//}
		//else 
		//{
		//	vector<string>::iterator it = find(elems.begin(), elems.end(), query.s);
		//	if (query.type == "find")
		//	{
		//		writeSearchResult(it != elems.end());
		//	}
		//	else if (query.type == "add") 
		//	{
		//		if (it == elems.end())
		//			elems.push_back(query.s);
		//	}
		//	else if (query.type == "del") 
		//	{
		//		if (it != elems.end())
		//			elems.erase(it);
		//	}
		//}
	}

	void processQueries()
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			processQuery(readQuery());
		}

		for (int i = 0; i < output.size(); i++)
		{
			cout << output[i];
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);

	int bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();

	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.