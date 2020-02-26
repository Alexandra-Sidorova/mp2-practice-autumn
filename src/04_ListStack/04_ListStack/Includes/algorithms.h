#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "TStack.h"
#include "TListStack.h"
#include "TArrayStack.h"
#include "TCouple.h"
#include "exceptions.h"

#include <cstring>
#include <cctype>


using namespace std;

template<typename ValType>
class Algorithms
{
private:
	TStack<char>* stackOperations; // 1
	TStack<char>* stackOperands;  // 2
	TStack<ValType>* stackResults;

    int GetPriority(const char);
	bool IsOperation(const char);
	void GetCountAndListOfVariables(int&, string&);

public:
	Algorithms(typeStack);

    TCouple<ValType>* SetDataOfVariables(string, int&);
    string CreateRPN(string);
    double CalculateRPN(string, TCouple<ValType>*, int);
};
//-----------------------------------------------------------

template<typename ValType>
int Algorithms<ValType>::GetPriority(const char _oper)
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
bool Algorithms<ValType>::IsOperation(const char _s)
{
    return (_s == '+' || _s == '-' || _s == '*' || _s == '/' ||
        _s == '(' || _s == ')');
};

template<typename ValType>
void Algorithms<ValType>::GetCountAndListOfVariables(int& _count, string& _str)
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
//-----------------------------------------------------------
template<typename ValType>
Algorithms<ValType>::Algorithms(typeStack _type)
{
	stackOperations = TStack<char>::Create(_type);
	stackOperands = TStack<char>::Create(_type);
	stackResults = TStack<double>::Create(_type);
};
//-----------------------------------------------------------

template<typename ValType>
TCouple<ValType>* Algorithms<ValType>::SetDataOfVariables(string _str, int& _countData)
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
string Algorithms<ValType>::CreateRPN(string _str)
{
    if (_str.length() == 0)
        throw Exception("Error: String is empty!");

    for (int i = 0; i < _str.length(); i++)
    {
        char symbol = static_cast<char>(_str[i]);

        if (symbol == ' ')  // space processing
            continue;

        if (IsOperation(symbol))  // operation processing
        {
            if (symbol == '(')
            {
				stackOperations->Push(symbol);
                continue;
            }

            if (symbol == ')')
            {
				bool flag =  false;

				while (!stackOperations->IsEmpty())
				{
					if (stackOperations->TopWatch() != '(')
					{
						stackOperands->Push(stackOperations->TopWatch());
						stackOperations->Pop();
						continue;
					}

					stackOperations->Pop(); // delete '('
					flag = true;
					break;
				}

				if(stackOperations->IsEmpty() && !flag)
					throw Exception("Error: Not correct the string - didn't find '('!");

                continue;
            }

            if ((stackOperations->IsEmpty()) || (GetPriority(symbol) > GetPriority(stackOperations->TopWatch())))
            {
				stackOperations->Push(symbol);
                continue;
            }

            while((!stackOperations->IsEmpty()) && (GetPriority(symbol) <= GetPriority(stackOperations->TopWatch())))
            {
				stackOperands->Push(stackOperations->TopWatch());
				stackOperations->Pop();
            }

			stackOperations->Push(symbol);
            continue;
        }

        if (isalpha(symbol))  // variable processing
        {
			stackOperands->Push(symbol);
            continue;
        }

        throw Exception("Error: The symbols are not correct in string!");  // no operation, no space, no letter
    }

    while (!stackOperations->IsEmpty())
    {
		stackOperands->Push(stackOperations->TopWatch());
		stackOperations->Pop();
    }

    string rpn;

    while (!stackOperands->IsEmpty())
    {
        rpn += stackOperands->TopWatch();
		stackOperands->Pop();
    }

    for (int i = 0; i < (rpn.length() / 2); i++)  // reverse rpn
        swap(rpn[i], rpn[rpn.length() - 1 - i]);

    return rpn;
};

template<typename ValType>
double Algorithms<ValType>::CalculateRPN(string _str, TCouple<ValType>* _data, int _countData)
{
    if (_str.length() == 0)
        throw Exception("Error: String is empty!");

    for (int i = 0; i < _str.length(); i++)
    {
        char symbol = static_cast<char>(_str[i]);

        if (!IsOperation(symbol))
        {
            for (int j = 0; j < _countData; j++)
            {
                if (_data[j].var == symbol)
                {
					stackResults->Push(static_cast<double>(_data[j].value));
                    break;
                }
            }

            continue;
        }

        double rightOperand = stackResults->TopWatch();
		stackResults->Pop();

        double leftOperand = stackResults->TopWatch();
		stackResults->Pop();

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

		stackResults->Push(res);
    }

    return stackResults->TopWatch();
};

#endif