#ifndef _RPN_H_
#define _RPN_H_

#include "TStack.h"
#include "TCouple.h"
#include "exceptions.h"

#include <cstring>
#include <cctype>

using namespace std;

template<typename ValType>
class RPN
{
private:
    static int GetPriority(const char);
    static bool IsOperation(const char);
    static void GetCountAndListOfVariables(int&, string&);

public:
    static TCouple<ValType>* SetDataOfVariables(string, int&);
    static string CreateRPN(string);
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
void RPN<ValType>::GetCountAndListOfVariables(int& _count, string& _str)
{
    string uniqueVariables;
    _count = 0;

    for (int i = 0; i < _str.length(); i++)
    {
        char symbol = static_cast<char>(_str[i]);

        if ((symbol != ' ') && (!IsOperation(symbol)) && (uniqueVariables.find(symbol) == string::npos))
        {
            uniqueVariables += symbol;
            _count++;
        }
    }

    _str = uniqueVariables;
};

template<typename ValType>
TCouple<ValType>* RPN<ValType>::SetDataOfVariables(string _str, int& _countData)
{
    _countData = 0;
    GetCountAndListOfVariables(_countData, _str);

    TCouple<ValType>* data = new TCouple<ValType>[_countData];

    for (int i = 0; i < _countData; i++)
    {
        data[i].var = _str[i];
        cout << "Variable " << _str[i] << " : ";
        cin >> data[i].value;
    }

    return data;
}

template<typename ValType>
string RPN<ValType>::CreateRPN(string _str)
{
    if (_str.length() == 0)
        throw Exception("Error: String is empty!");

    TStack<char> st1(_str.length() + 1);  // operations
    TStack<char> st2(_str.length() + 1);  // operands

    for (int i = 0; i < _str.length(); i++)
    {
        char symbol = static_cast<char>(_str[i]);

        if (symbol == ' ')  // space processing
            continue;

        if (IsOperation(symbol))  // operation processing
        {
            if (symbol == '(')
            {
                st1.Push(symbol);
                continue;
            }

            if (symbol == ')')
            {
				bool flag =  false;

				while (!st1.IsEmpty())
				{
					if (st1.TopWatch() != '(')
					{
						st2.Push(st1.TopWatch());
						st1.Pop();
						continue;
					}

					st1.Pop(); // delete '('
					flag = true;
					break;
				}

				if(st1.IsEmpty() && !flag)
					throw Exception("Error: Not correct the string - didn't find '('!");

                continue;
            }

            if ((st1.IsEmpty()) || (GetPriority(symbol) >= GetPriority(st1.TopWatch())))
            {
                st1.Push(symbol);
                continue;
            }

            while((!st1.IsEmpty()) && (GetPriority(symbol) <= GetPriority(st1.TopWatch())))
            {
                st2.Push(st1.TopWatch());
                st1.Pop();
            }

            st1.Push(symbol);
            continue;
        }

        if (isalpha(symbol))  // variable processing
        {
            st2.Push(symbol);
            continue;
        }

        throw Exception("Error: The symbols are not correct in string!");  // no operation, no space, no letter
    }

    while (!st1.IsEmpty())
    {
        st2.Push(st1.TopWatch());
        st1.Pop();
    }

    string rpn;

    while (!st2.IsEmpty())
    {
        rpn += st2.TopWatch();
        st2.Pop();
    }

    for (int i = 0; i < (rpn.length() / 2); i++)  // reverse rpn
        swap(rpn[i], rpn[rpn.length() - 1 - i]);

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
        char symbol = static_cast<char>(_str[i]);

        if (!IsOperation(symbol))
        {
            for (int j = 0; j < _countData; j++)
            {
                if (_data[j].var == symbol)
                {
                    value.Push(static_cast<double>(_data[j].value));
                    break;
                }
            }

            continue;
        }

        double rightOperand = value.TopWatch();
        value.Pop();

        double leftOperand = value.TopWatch();
        value.Pop();

        double res = 0;

        switch (symbol)
        {
        case '+':
            res = leftOperand + rightOperand;
            break;
        case '-':
            res = leftOperand - rightOperand;
            break;
        case '*':
            res = leftOperand * rightOperand;
            break;
        case '/':
            if (rightOperand == 0)
                throw Exception("Error: Division by zero!");
            res = leftOperand / rightOperand;
            break;
        }

        value.Push(res);
    }

    return value.TopWatch();
};

#endif