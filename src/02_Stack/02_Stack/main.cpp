#include "Includes/RPN.h"
#include "Includes/TCouple.h"

#include <string.h>
#include <iostream>

using namespace std;

void main()
{
    cout << "##### Reverse Polish notation #####" << endl << endl;
    cout << "Enter string to convert to Revers Polish notation and press <Enter>: ";

    try
    {
        string str;
        getline(cin, str);

        cout << "Converting..." << endl;
        string rpn = RPN<double>::CreateRPN(str);
        cout << "Reverse Polish Notation: " << rpn << endl;

		int countVariables = RPN<double>::GetCountVariables(str);

        cout << "Enter variables and its values: " << endl;
        TCouple<double>* data = new TCouple<double>[countVariables];

        char* variables = RPN<double>::GetListOfVariables(str);
        for (int i = 0; i < countVariables; i++)
        {
            data[i].var = variables[i];
            cout << "Variable " << variables[i] << " : ";
            cin >> data[i].value;
        }

        double result = RPN<double>::CalculateRPN(rpn, data, countVariables);
        cout << "Result: " << result;
        //char str[] = "A + B   * (C -D)/(F+E)+K";
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }
}