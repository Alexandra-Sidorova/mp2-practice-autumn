#ifndef _TMATRIX_H_
#define _TMATRIX_H_

#include <iostream>

#include "exceptions.h"

template<typename ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix();
	TMatrix(int size = 5);
	TMatrix(const TMatrix&);
	TMatrix(const TVector<TVector<ValType> >);
	~TMatrix();

	const TMatrix& operator=(const TMatrix&);

	TMatrix operator+(const TMatrix&);
	TMatrix operator-(const TMatrix&);
	TMatrix operator*(const TMatrix&);

	TMatrix operator+(ValType);
	TMatrix operator-(ValType);
	TMatrix operator*(ValType);

	TMatrix operator*(const TVector<ValType>&);

	bool operator==(const TMatrix&) const;
	bool operator!=(const TMatrix&) const;

	friend istream operator>>(istream& _in, TMatrix& _matrix);
	friend ostream operator<<(ostream& _out, const TMatrix& _matrix);
};

//---------------------------------------------------------------------------

template<typename ValType>
TMatrix<ValType>::TMatrix()
{

}

#endif
