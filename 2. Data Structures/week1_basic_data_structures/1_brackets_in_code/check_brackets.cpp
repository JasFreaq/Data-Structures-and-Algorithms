#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket
{
	Bracket(char type, int position) :
		type(type),
		position(position)
	{}

	bool Matchc(char c)
	{
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;

		return false;
	}

	char type;
	int position;
};

int main()
{
	std::string text;
	getline(cin, text);
	int wrongPos = -1;

	std::stack <Bracket> opening_brackets_stack;
	for (int position = 0; position < text.length(); ++position)
	{
		char next = text[position];

		if (next == '(' || next == '[' || next == '{')
		{
			Bracket bracket(next, position);
			opening_brackets_stack.push(bracket);
		}

		if (next == ')' || next == ']' || next == '}')
		{
			if (opening_brackets_stack.empty())
			{
				wrongPos = position;
				break;
			}
			else
			{
				Bracket bracket = opening_brackets_stack.top();
				if (bracket.Matchc(next))
				{
					opening_brackets_stack.pop();
				}
				else
				{
					wrongPos = position;
					break;
				}
			}
		}
	}

	if (wrongPos != -1)
	{
		cout << wrongPos + 1 << endl;
	}
	else if (opening_brackets_stack.empty())
	{
		cout << "Success\n";
	}
	else
	{
		Bracket bracket = opening_brackets_stack.top();
		cout << bracket.position + 1 << endl;
	}

	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.