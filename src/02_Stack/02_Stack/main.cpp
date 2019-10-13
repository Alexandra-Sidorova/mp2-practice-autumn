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
        getline(cin, str);  // A + B   * (C -D)/(F+E)+K

        cout << "Converting..." << endl;
        string rpn = RPN<double>::CreateRPN(str);
        cout << "Reverse Polish Notation: " << rpn << endl;

        int countVariables = 0;
        TCouple<double>* data = RPN<double>::SetDataOfVariables(str, countVariables);

        double result = RPN<double>::CalculateRPN(rpn, data, countVariables);
        cout << "Result: " << result;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }
}