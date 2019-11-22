#include "Includes/TList_TPolinom.h"
#include "Includes/TPolinom.h"
#include "Includes/exceptions.h"

#include <conio.h>
#include <iostream>

void main()
{
	cout << "##### TEST <Polinom> #####" << endl << endl;

	try
	{
		cout << "### Testing of constructors ###" << endl << endl;

		cout << "Default: ";
		TPolinom defPolinom;
		cout << defPolinom << endl;

		cout << "List Parameterized: ";
		TNode<int, float>* node3 = new TNode<int, float>(123, 5);
		TNode<int, float>* node2 = new TNode<int, float>(100, 10, node3);
		TNode<int, float>* node1 = new TNode<int, float>(30, 3, node2);
		TNode<int, float>* node0 = new TNode<int, float>(2, 7, node1);
		TList<int, float>* listParametr = new TList<int, float>(node0);
		TPolinom listPolinom(listParametr);
		cout << listPolinom << endl;

		cout << "String Parameterized (5x^3 + 12x^2y^3 - 21x^1y^2z^3): ";
		string str1 = "5x^3 + 12x^2y^3 - 21x^1y^2z^3";
		TPolinom stringPolinom1(str1);
		cout << stringPolinom1 << endl;

		cout << "Copy Parameterized (ListPolinom): ";
		TPolinom copyPolinom(listPolinom);
		cout << copyPolinom << endl;

		cout << "String Parameterized (10x^10): ";
		string str2 = "10x^10";
		TPolinom stringPolinom2(str2);
		cout << stringPolinom2 << endl;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << "### Testing of operator = ###" << endl << endl;

		cout << "Polinom: ";
		TPolinom stringPolinom("5x^3 + 12x^2y^3 - 21x^1y^2z^3 - 7z^2x^1");
		cout << stringPolinom << endl;

		cout << "New Polinom = Polinom : ";
		TPolinom newPolinom = stringPolinom;
		cout << newPolinom << endl;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << "### Testing of operator + ###" << endl << endl;

		cout << "Polinom1: ";
		TPolinom polinom1("5x^2 + 15y^2z^3");
		cout << polinom1;
		cout << "Polinom2: ";
		TPolinom polinom2("10z^2 - 8y^2z^3");
		cout << polinom2;
		cout << "Polinom1 + Polinom2: ";
		TPolinom sum = polinom1 + polinom2;
		cout << sum << endl;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << "### Testing of operator - ###" << endl << endl;

		cout << "Polinom1: ";
		TPolinom polinom1("5x^2 + 15y^2z^3");
		cout << polinom1;
		cout << "Polinom2: ";
		TPolinom polinom2("10z^2 - 8y^2z^3");
		cout << polinom2;
		cout << "Polinom1 - Polinom2: ";
		TPolinom sub = polinom1 - polinom2;
		cout << sub << endl;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	try
	{
		cout << "### Testing of operator * ###" << endl << endl;

		cout << "Polinom1: ";
		TPolinom polinom1("5x^2 + 15y^2z^3 + 6x^3y^2z^5");
		cout << polinom1;
		cout << "Polinom2: ";
		TPolinom polinom2("10z^2 - 8y^2z^3");
		cout << polinom2;
		cout << "Polinom1 * Polinom2: ";
		TPolinom sub1 = polinom1 * polinom2;
		cout << sub1 << endl;

		cout << "Polinom3: ";
		TPolinom polinom3("5x^5 + 15y^2z^3 + 6x^3y^2z^5");
		cout << polinom3;
		cout << "Polinom4: ";
		TPolinom polinom4("10z^2 - 8y^8z^9");
		cout << polinom4;
		cout << "Polinom3 * Polinom4: ";
		TPolinom sub2 = polinom3 * polinom4;
		cout << sub2 << endl;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}
};