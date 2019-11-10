#include "Includes/TList.h"
#include "Includes/algorithms.h"
#include "Includes/exceptions.h"

#include <conio.h>
#include <iostream>

void main()
{
	cout << "########## Array Stack and List Stack ##########" << endl << endl;
	cout << "##### TEST <List> #####" << endl << endl;
	
	try
	{
		cout << "### Testing of constructors ###" << endl;

		cout << "Defalt: ";
		TList<int, int> listDef;
		listDef.Print();

		cout << "Parameterized: ";
		TNode<int, int>* node3 = new TNode<int, int>(10, NULL);
		TNode<int, int>* node2 = new TNode<int, int>(9, NULL, node3);
		TNode<int, int>* node1 = new TNode<int, int>(8, NULL, node2);
		TNode<int, int>* node0 = new TNode<int, int>(7, NULL, node1);
		TList<int, int> listParametr(node0);
		listParametr.Print();

		cout << "Copy: ";
		TList<int, int> listCopy(listParametr);
		listCopy.Print();
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	cout << endl << "### Testing of methods ###" << endl;
	try
	{
		cout << endl << "### Testing of search ###" << endl;
		cout << "List: ";
		TNode<int, int>* node3 = new TNode<int, int>(10, NULL);
		TNode<int, int>* node2 = new TNode<int, int>(9, NULL, node3);
		TNode<int, int>* node1 = new TNode<int, int>(8, NULL, node2);
		TNode<int, int>* node0 = new TNode<int, int>(7, NULL, node1);
		TList<int, int> list(node0);
		list.Print();

		cout << "Search 9: " << list.Search(9) << endl;
		cout << "Search 1: " << list.Search(1) << endl;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}
	
	try
	{
		cout << endl << "### Testing of popBegin ###" << endl;
		cout << "ListA: ";
		TList<int, int> listA;
		listA.Print();
		cout << "ListA.PopBegin (25): ";
		listA.PopBegin(25, NULL);
		listA.Print();

		cout << endl << "ListB: ";
		TNode<int, int>* node3 = new TNode<int, int>(10, NULL);
		TNode<int, int>* node2 = new TNode<int, int>(9, NULL, node3);
		TNode<int, int>* node1 = new TNode<int, int>(8, NULL, node2);
		TNode<int, int>* node0 = new TNode<int, int>(7, NULL, node1);
		TList<int, int> listB(node0);
		listB.Print();
		cout << "ListB.PopBegin (1): ";
		listB.PopBegin(1, NULL);
		listB.Print();
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << "### Testing of popEnd ###" << endl;
		cout << "ListA: ";
		TList<int, int> listA;
		listA.Print();
		cout << "ListA.PopEnd (25): ";
		listA.PopEnd(25, NULL);
		listA.Print();

		cout << endl << "ListB: ";
		TNode<int, int>* node3 = new TNode<int, int>(10, NULL);
		TNode<int, int>* node2 = new TNode<int, int>(9, NULL, node3);
		TNode<int, int>* node1 = new TNode<int, int>(8, NULL, node2);
		TNode<int, int>* node0 = new TNode<int, int>(7, NULL, node1);
		TList<int, int> listB(node0);
		listB.Print();
		cout << "ListB.PopEnd (1): ";
		listB.PopEnd(1, NULL);
		listB.Print();
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << "### Testing of popBefore ###" << endl;
		cout << "ListA: ";
		TNode<int, int>* node3 = new TNode<int, int>(10, NULL);
		TNode<int, int>* node2 = new TNode<int, int>(9, NULL, node3);
		TNode<int, int>* node1 = new TNode<int, int>(8, NULL, node2);
		TNode<int, int>* node0 = new TNode<int, int>(7, NULL, node1);
		TList<int, int> listA(node0);
		listA.Print();
		cout << "ListA.popBefore 9 (30): ";
		listA.PopBefore(9, 30, NULL);
		listA.Print();
		cout << "ListA.popBefore 7 (1) [in begin]: ";
		listA.PopBefore(7, 1, NULL);
		listA.Print();
		cout << "ListA.popBefore 29 (28): ";
		listA.PopBefore(29, 28, NULL);
		listA.Print();
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << "### Testing of popAfter ###" << endl;
		cout << "ListA: ";
		TNode<int, int>* node3 = new TNode<int, int>(10, NULL);
		TNode<int, int>* node2 = new TNode<int, int>(9, NULL, node3);
		TNode<int, int>* node1 = new TNode<int, int>(8, NULL, node2);
		TNode<int, int>* node0 = new TNode<int, int>(7, NULL, node1);
		TList<int, int> listA(node0);
		listA.Print();
		cout << "ListA.popAfter 9 (30): ";
		listA.PopAfter(9, 30, NULL);
		listA.Print();
		cout << "ListA.popAfter 10 (100) [in end]: ";
		listA.PopAfter(10, 100, NULL);
		listA.Print();
		cout << "ListA.popAfter 29 (28): ";
		listA.PopAfter(29, 28, NULL);
		listA.Print();
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << "### Testing of delete ###" << endl;
		cout << "ListA: ";
		TNode<int, int>* node3 = new TNode<int, int>(10, NULL);
		TNode<int, int>* node2 = new TNode<int, int>(9, NULL, node3);
		TNode<int, int>* node1 = new TNode<int, int>(8, NULL, node2);
		TNode<int, int>* node0 = new TNode<int, int>(7, NULL, node1);
		TList<int, int> listA(node0);
		listA.Print();
		cout << "ListA.Delete 8: ";
		listA.Delete(8);
		listA.Print();
		cout << "ListA.Delete 10 [end]: ";
		listA.Delete(10);
		listA.Print();
		cout << "ListA.Delete 7 [begin]: ";
		listA.Delete(7);
		listA.Print();
		cout << "ListA.Delete 100: ";
		listA.Delete(100);
		listA.Print();
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	cout << "##### REVERSE POLISH NOTATION #####" << endl << endl;

	try 
	{
		cout << "Enter type of stack. Array Stack - 0, List Stack - 1: ";
		string choose, str;
		getline(cin, choose);

		cout << "Enter the string: ";
		getline(cin, str);  // A + B   * (C -D)/(F+E)+K

		switch (static_cast<char>(choose[0]))
		{
			case '0':
			{
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