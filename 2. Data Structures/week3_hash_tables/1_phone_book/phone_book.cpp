#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Query
{
	string type, name;
	int number;
};

vector<Query> read_queries()
{
	int n;
	cin >> n;
	vector<Query> queries(n);
	for (int i = 0; i < n; i++)
	{
		cin >> queries[i].type;
		if (queries[i].type == "add")
			cin >> queries[i].number >> queries[i].name;
		else
			cin >> queries[i].number;
	}
	return queries;
}

void write_responses(const vector<string>& result)
{
	for (size_t i = 0; i < result.size(); i++)
		std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries)
{
	vector<string> result;
	vector<Query> contacts;
	vector<string> database(10000000, "-");

	for (size_t i = 0; i < queries.size(); i++)
	{
		if (queries[i].type == "add")
		{
			database[queries[i].number] = queries[i].name;
		}
		else if (queries[i].type == "del")
		{
			database[queries[i].number] = "-";
		}
		else if (queries[i].type == "find")
		{
			if (database[queries[i].number] == "-")
			{
				result.push_back("not found");
			}
			else
			{
				result.push_back(database[queries[i].number]);
			}
		}
	}

	return result;
}

int main()
{
	write_responses(process_queries(read_queries()));
	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.