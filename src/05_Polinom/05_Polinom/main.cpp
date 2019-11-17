#include "Includes/TList_TPolinom.h"
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
		TNode<int, float>* node3 = new TNode<int, float>(0, 5);
		TNode<int, float>* node2 = new TNode<int, float>(0, 10, node3);
		TNode<int, float>* node1 = new TNode<int, float>(0, 3, node2);
		TNode<int, float>* node0 = new TNode<int, float>(0, 7, node1);
		TList<int, float> listParametr(node0);
		cout << listParametr;
		listParametr.SortData();
		cout << listParametr;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}
};