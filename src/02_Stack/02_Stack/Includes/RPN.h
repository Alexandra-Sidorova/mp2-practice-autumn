#ifndef _RPN_H_
#define _RPN_H_

#include "TStack.h"
#include "TCouple.h"
#include "exceptions.h"

#include <cstring>

using namespace std;

template<typename ValType>
class RPN
{
private:
	static int GetPriority(const char);
	static bool IsOperation(const char);

public:
	static int GetCountVariables(const char*);
	static string CreateRPN(const char*);
	static double CalculateRPN(string, TCouple<ValType>*, int);
};

//-----------------------------------------------------------

template<typename ValType>
int RPN<ValType>::GetPriority(const char _oper)
{
	switch (_oper)
	{
	case '(':
		return 1;
	case ')':
		return 1;
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	default:
		throw Exception("Error: Invalid character!");
	}
};

template<typename ValType>
bool RPN<ValType>::IsOperation(const char _s)
{
	return (_s == '+' || _s == '-' || _s == '*' || _s == '/' ||
		_s == '(' || _s == ')');
};

template<typename ValType>
int RPN<ValType>::GetCountVariables(const char* _str)
{
	int count = 0;
	char* vars = new char[strlen(_str) + 1];
	memset(vars, 0, sizeof(char) * (strlen(_str) + 1));


	for (int i = 0; i < strlen(_str); i++)
	{
		char symbol = _str[i];

		if ((symbol != ' ') && (!IsOperation(symbol)) && (strchr(vars, symbol) == NULL))
				vars[count++] += symbol;
	}

	return count;
};

template<typename ValType>
string RPN<ValType>::CreateRPN(const char* _str)
{
	if (strlen(_str) == 0)
		throw Exception("Error: String is empty!");

	TStack<char> st1(strlen(_str) + 1);  // operations
	TStack<char> st2(strlen(_str) + 1);  // operands

	for (int i = 0; i < strlen(_str); i++)
	{
		if (_str[i] == ' ')
			continue;

		if (IsOperation(_str[i]))
		{
			if (_str[i] == '(')
			{
				st1.Push(_str[i]);
				continue;
			}

			if (_str[i] == ')')
			{
				while (st1.TopWatch() != '(')
					st2.Push(st1.Pop());

				st1.Pop(); // delete '('
				continue;
			}

			if (st1.IsEmpty())
			{
				st1.Push(_str[i]);
				continue;
			}

			if (GetPriority(_str[i]) >= GetPriority(st1.TopWatch()))
			{
				st1.Push(_str[i]);
				continue;
			}

			while(GetPriority(_str[i]) < GetPriority(st1.TopWatch()))
				st2.Push(st1.Pop());
		}

		st2.Push(_str[i]);
	}

	while (!st1.IsEmpty())
	{
		char tmp = st1.Pop();
		st2.Push(tmp);
	}

	string rpn(st2.GetSize(), 0);

	while (!st2.IsEmpty())
	{
		rpn[st2.GetSize() - 1] = st2.TopWatch();
		st2.Pop();
	}

	return rpn;
};

template<typename ValType>
double RPN<ValType>::CalculateRPN(string _str, TCouple<ValType>* _data, int _countData)
{
	if (_str.length() == 0)
		throw Exception("Error: String is empty!");

	TStack<double> value(_str.length());

	for (int i = 0; i < _str.length(); i++)
	{
		if (!IsOperation(static_cast<char>(_str[i])))
		{
			for (int j = 0; j < _countData; j++)
			{
				if (_data[j].var == static_cast<char>(_str[i]))
				{
					value.Push(static_cast<double>(_data[j].value));
					break;
				}
			}

			continue;
		}

		double rightOperand = value.Pop();
		double leftOperand = value.Pop();
		double res = 0;

		if (static_cast<char>(_str[i]) == '+')
			res = leftOperand + rightOperand;
		if (static_cast<char>(_str[i]) == '-')
			res = leftOperand - rightOperand;
		if (static_cast<char>(_str[i]) == '*')
			res = leftOperand * rightOperand;
		if (static_cast<char>(_str[i]) == '/')
			res = leftOperand / rightOperand;

		value.Push(res);
	}

	return value.Pop();
}

#endif