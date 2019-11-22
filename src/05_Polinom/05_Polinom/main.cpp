#include "Includes/TList_TPolinom.h"
#include "Includes/TPolinom.h"
#include "Includes/exceptions.h"

#include <conio.h>
#include <iostream>

void main()
{
	cout << "##### TEST <List> #####" << endl << endl;

	try
	{
		cout << "### Testing of constructors ###" << endl;

		cout << "Parameterized: ";
		TNode<int, float>* node3 = new TNode<int, float>(123, 5);
		TNode<int, float>* node2 = new TNode<int, float>(100, 10, node3);
		TNode<int, float>* node1 = new TNode<int, float>(30, 3, node2);
		TNode<int, float>* node0 = new TNode<int, float>(9, 7, node1);
		TList<int, float>* listParametr = new TList<int, float>(node0);

		TPolinom polinom(listParametr);
		cout << "polinom: " << polinom;
		
		string str = "5x^3 + 12x^2y^3 -21x^1y^2z^3";
		TPolinom poli(str);
		cout << "poli: " << poli;

		TPolinom copy;
		copy = polinom;
		cout << "copy.polinom: " << copy;
		copy = -poli;
		cout << "copy.-poly: " << copy;

		TPolinom sum;
		sum = copy + polinom;
		cout << "sum = copy + polinom: " << sum;

		TPolinom min;
		min = sum - polinom;
		cout << "min = sum - polinom: " << min;
		cout << "sum: " << sum;

		string test = "4.215z^2^ -3";
		TPolinom politest(test);
		cout << politest;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}
};