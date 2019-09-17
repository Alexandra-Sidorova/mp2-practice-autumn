#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "Includes/TMatrix.h"
#include "Includes/exceptions.h"

using namespace std;

void main()
{

    TMatrix<int> A(5), B(5), C(3);
    TVector<int> v1(5), v2(3);

    for (int i = 0; i < A.GetSize(); i++)  // filling out
    {
        v1[i] = rand() % 10;

        for (int j = 0; j < A.GetSize() - i; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < C.GetSize(); i++)  // filling out
    {
        v2[i] = rand() % 10;

        for (int j = 0; j < C.GetSize() - i; j++)
            C[i][j] = rand() % 10;
    }
    
    try  // output
    {
        cout << "##### Matrices #####" << endl << endl;
        cout << "Matrix A:" << endl;
        cout << A << endl;
        cout << "Matrix B:" << endl;
        cout << B << endl;
        cout << "Matrix C:" << endl;
        cout << C << endl;

        cout << "##### Vectors #####" << endl << endl;
        cout << "Vector v1:" << endl;
        cout << v1 << endl << endl;
        cout << "Vector v2:" << endl;
        cout << v2 << endl << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    try  // adding
    {
        cout << "##### Adding #####" << endl << endl;
        cout << "Matrix A + B:" << endl;
        cout << A + B << endl;
        cout << "Matrix A + C:" << endl;
        cout << A + C << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    try  // subtraction
    {
        cout << "##### Subtraction #####" << endl << endl;
        cout << "Matrix A - B:" << endl;
        cout << A - B << endl;
        cout << "Matrix A - C:" << endl;
        cout << A - C << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    try  // multiplication of matrices
    {
        cout << "##### Multiplication of matrices #####" << endl << endl;
        cout << "Matrix A * B:" << endl;
        cout << A * B << endl;
        cout << "Matrix A * C:" << endl;
        cout << A * C << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    try  // actions between matrices and numbers
    {
        cout << "##### Actions between matrices and numbers #####" << endl << endl;
        cout << "A + 10:" << endl;
        cout << A + 10 << endl;
        cout << "Matrix B - 6:" << endl;
        cout << B - 6 << endl;
        cout << "C * 4:" << endl;
        cout << C * 4 << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    try  // multiplication of matrix and vector
    {
        cout << "##### Multiplication of matrix and vector #####" << endl << endl;
        cout << "A * v1:" << endl;
        cout << A * v1 << endl << endl;
        cout << "A * v2:" << endl;
        cout << A * v2 << endl << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    try  // determinant
    {
        cout << "##### Determinants of matrices #####" << endl << endl;
        cout << "det|A|:" << endl;
        cout << A.Determinant() << endl << endl;
        cout << "det|B|:" << endl;
        cout << B.Determinant() << endl << endl;
        cout << "det|C|:" << endl;
        cout << C.Determinant() << endl << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    try  // comparisons
    {
        cout << "##### Comparisons #####" << endl << endl;
        cout << "A == B? : ";
        cout << (A == B) << endl << endl;
        cout << "A == A? : ";
        cout << (A == A) << endl << endl;
        cout << "A != B? : ";
        cout << (A != B) << endl << endl;
        cout << "C != C? : ";
        cout << (C != C) << endl << endl;
    }
    catch (Exception ex)
    {
        cout << ex.what() << endl << endl;
    }

    int c =_getch();
}