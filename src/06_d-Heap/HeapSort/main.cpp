#include "Heapsort.h"
#include "exceptions.h"

#include <cmath>
#include <iostream>
#include <time.h>

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	cout << "##### HEAPSORT TESTS ######" << endl;

	try
	{
		cout << endl << "RANDOM ARRAY IN [A, B]" << endl;
		float a, b;
		int size = 0;
		
		cout << "Enter the array size:";
		cin >> size;
		if (size <= 0)
			throw Exception("Size must be positive!");

		cout << "Enter the A: ";
		cin >> a;
		cout << "Enter the B: ";
		cin >> b;

		float* elements = new float[size];
		for (int i = 0; i < 10; i++)
		{
			elements[i] = a + rand() % (int)(b - a + 1);
			cout << elements[i] << " ";
		}

		cout << endl << "Sorting..." << endl;

		HeapSort<float>::Sort(elements, 10);
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
		cout << endl << "INCORRECT SIZE -100 OF RANDOM ARRAY IN [-20; 20] " << endl;
		int* elements = new int[10];

		for (int i = 0; i < 10; i++)
		{
			elements[i] = rand() % 41 - 20;
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