#ifndef _TMATRIX_H_
#define _TMATRIX_H_

#include <iostream>

#include "exceptions.h"
#include "TVector.h"

template<typename ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int size = 5);
	TMatrix(const TMatrix&);
	TMatrix(const TVector<TVector<ValType> >&);
	virtual ~TMatrix();

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

template<typename ValueType>
TMatrix<ValueType>::TMatrix(int size) : TVector<TVector<ValueType> >(size)
{
	for (int i = 0; i < size; i++)
		elem[i] = TVector<Valtype>(size - i, i);
};

template<typename ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& _copy) : TVector<TVector<ValueType> >(_copy)
{};

template<typename ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& _vector) : TVector<TVector<ValueType> >(_vector)
{};

template<typename ValType>
TMatrix<ValType>::~TMatrix()
{};

template<typename ValType>
const TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& _copy)
{
	if (this == &_copy)
		return *this;

	if (size != _copy.size)
	{
		delete[] elem;
		elem = new TVector<ValType>[_copy.size];
	}

	size = _copy.size;
	startIndex = _copy.startIndex;

	for (int i = 0; i < size; i++)
		elem[i] = _copy.elem[i];

	return *this;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& _add)
{
	if (size != _add.size)
		throw Exception("Not correct size of adding matrix!");

	result = TMatrix<ValType>(size);
}
;


#endif