#include "Includes/RPN.h"

#include <string.h>
#include <iostream>

using namespace std;

void main()
{
	char str[] = "A + B   * (C -D)/(F+E)+K";
	string rpn = RPN<int>::CreateRPN(str);
	cout << rpn;

}