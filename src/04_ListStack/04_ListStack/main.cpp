#include "Includes/TList.h"
#include "Includes/algorithms.h"
#include "Includes/exceptions.h"

#include <conio.h>
#include <iostream>

void main()
{
	cout << "########## Array Stack and List Stack ##########" << endl << endl;
	cout << "##### REVERSE POLISH NOTATION #####" << endl << endl;

	try 
	{
		cout << "Enter type of stack. Array Stack - 0, List Stack - 1: ";
		string choose, str;
		getline(cin, choose);

		switch (static_cast<char>(choose[0]))
		{
			case '0':
			{
				cout << "Enter the string: ";
				getline(cin, str);  // A + B   * (C -D)/(F+E)+K

				Algorithms<double> postfix(arrayStack);
				cout << "Converting..." << endl;
				string rpn = postfix.CreateRPN(str);
				cout << "Reverse Polish Notation: " << rpn << endl;

				int countVariables = 0;
				TCouple<double>* data = postfix.SetDataOfVariables(str, countVariables);

				double result = postfix.CalculateRPN(rpn, data, countVariables);
				cout << "Result: " << result;
				break;
			}
			case '1':
			{
				cout << "Enter the string: ";
				getline(cin, str);  // A + B   * (C -D)/(F+E)+K

				Algorithms<double> postfix(listStack);
				cout << "Converting..." << endl;
				string rpn = postfix.CreateRPN(str);
				cout << "Reverse Polish Notation: " << rpn << endl;

				int countVariables = 0;
				TCouple<double>* data = postfix.SetDataOfVariables(str, countVariables);

				double result = postfix.CalculateRPN(rpn, data, countVariables);
				cout << "Result: " << result;
				break;
			}
			default:
			{
				throw Exception("Error! Type of stack is not correct!");
				break;
			}
		}
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	_getch();
}