#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "Includes/TMatrix.h"
#include "Includes/exceptions.h"

using namespace std;

void main()
{
	try 
	{
		TMatrix<int> A(5), B(5,1), C(5);
		bool flag;

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5 - i; j++)
			{
				A[i][j] = rand() % 10;
				B[i][j] = rand() % 10 + 10;
			}

		cout << "Matrix A:" << endl << A << endl;
		cout << "Matrix B:" << endl << B << endl;
		cout << "b focus:" << endl << B.GetFocus() << endl;
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}

	int c =_getch();
}