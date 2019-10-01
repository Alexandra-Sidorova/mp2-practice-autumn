#include "Includes/RPN.h"
#include "Includes/TCouple.h"

#include <string.h>
#include <iostream>

using namespace std;

void main()
{
	char str[] = "A + B   * (C -D)/(F+E)+K";
	//char str[] = "A + B * C / A ";
	string rpn = RPN<double>::CreateRPN(str);
	cout << rpn << endl;
	//cout << RPN<double>::GetCountVariables(str);

	TCouple<double>* data = new TCouple<double>[RPN<double>::GetCountVariables(str)];

	for (int i = 0; i < RPN<double>::GetCountVariables(str); i++)
		cin >> data[i].var >> data[i].value;

	double result = RPN<double>::CalculateRPN(rpn, data, RPN<double>::GetCountVariables(str));

	cout << result;

}