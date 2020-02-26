#include "Includes/Heapsort.h"
#include "exceptions.h"

#include <iostream>

using namespace std;

void main()
{
	cout << "##### HEAPSORT TESTS ######" << endl;

	try
	{
		int *elements = new int[10];

		for (int i = 0; i < 10; i++)
		{
			elements[i] = rand() % 20 - 10;
			cout << elements[i] << " ";
		}

		cout << endl << "Sorting..." << endl;

		HeapSort<int>::Sort(elements, 10);
		for (int i = 0; i < 10; i++)
		{
			cout << elements[i] << " ";
		}
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}
}