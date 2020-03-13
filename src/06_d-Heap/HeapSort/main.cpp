#include "Heapsort.h"
#include "exceptions.h"

#include <iostream>
#include <time.h>

#define RANDOM 30

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	cout << "##### HEAPSORT TESTS ######" << endl;

	try
	{
		cout << endl << "RANDOM ARRAY" << endl;
		int *elements = new int[10]; // float or double

		for (int i = 0; i < 10; i++)
		{
			elements[i] = rand() % RANDOM - RANDOM / 2; // [a, b]
			cout << elements[i] << " ";
		}

		cout << endl << "Sorting..." << endl;

		HeapSort<int>::Sort(elements, 10);
		for (int i = 0; i < 10; i++)
			cout << elements[i] << " ";
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << endl << "EMPTY ARRAY" << endl;
		int* elements = new int;

		cout << *elements << endl;
		cout << "Sorting..." << endl;
		
		HeapSort<int>::Sort(elements, 0);
		
		cout << *elements << endl;
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl;
	}

	try
	{
		cout << endl << "INCORRECT SIZE -100" << endl;
		int* elements = new int[10];

		for (int i = 0; i < 10; i++)
		{
			elements[i] = rand() % RANDOM - RANDOM / 2;
			cout << elements[i] << " ";
		}
		cout << endl << "Size = -100" << endl;
		cout << "Sorting..." << endl;

		HeapSort<int>::Sort(elements, -100);

		cout << *elements << endl;
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}
}