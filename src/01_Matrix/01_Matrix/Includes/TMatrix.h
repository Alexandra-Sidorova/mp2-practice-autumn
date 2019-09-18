#ifndef _TMATRIX_H_
#define _TMATRIX_H_

#include <iostream>

#include "exceptions.h"
#include "TVector.h"

using namespace std;

template<typename ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    TMatrix(int size = 10);
    TMatrix(const TMatrix&);
    TMatrix(const TVector<TVector<ValType> >&);
    ~TMatrix();

    ValType Determinant();

    const TMatrix& operator=(const TMatrix&);

    TMatrix operator+(const TMatrix&);
    TMatrix operator-(const TMatrix&);
    TMatrix operator*(const TMatrix&);

    TMatrix operator+(ValType);
    TMatrix operator-(ValType);
    TMatrix operator*(ValType);

    TVector<ValType> operator*(const TVector<ValType>&);

    bool operator==(const TMatrix&) const;
    bool operator!=(const TMatrix&) const;

    template<typename ValType> friend istream& operator>>(istream&, TMatrix<ValType>&);
    template<typename ValType> friend ostream& operator<<(ostream&, const TMatrix<ValType>&);
};

//---------------------------------------------------------------------------

template<typename ValType>
TMatrix<ValType>::TMatrix(int _size) : TVector<TVector<ValType> >(_size)
{
    if (_size <= 0)
        throw Exception("Not correct size of matrix!");

    for (int i = 0; i < _size; i++)
        this->elem[i] = TVector<ValType>(_size - i, i);
};

template<typename ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& _copy) : TVector<TVector<ValType> >(_copy)
{};

template<typename ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& _vector) : TVector<TVector<ValType> >(_vector)
{};

template<typename ValType>
ValType TMatrix<ValType>::Determinant()
{
    ValType det = this->elem[0][0];

    for (int i = 1; i < this->size; i++)
        det *= this->elem[i][0];

    return det;
};

template<typename ValType>
TMatrix<ValType>::~TMatrix()
{};

template<typename ValType>
const TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& _copy)
{
    TVector<TVector<ValType> >::operator=(_copy);
    return *this;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& _add)
{
    if (this->size != _add.size)
        throw Exception("Not correct size of adding matrix!");

    return TVector<TVector<ValType> >::operator+(_add);
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& _sub)
{
    if (this->size != _sub.size)
        throw Exception("Not correct size of adding matrix!");

    return TVector<TVector<ValType> >::operator-(_sub);
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& _factor)
{
    if (this->size != _factor.size)
        throw Exception("Not correct size of adding matrix!");

    TMatrix<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        for (int j = i; j < this->size; j++)
            for (int k = i; k <= j; k++)
                result.elem[i][j - i] += this->elem[i][k - i] * _factor.elem[k][j - k];
        
    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(ValType _add)
{
    TMatrix<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        result[i] = this->elem[i] + _add;

    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(ValType _sub)
{
    TMatrix<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        result[i] = this->elem[i] - _sub;

    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType _factor)
{
    TMatrix<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        result[i] = this->elem[i] * _factor;

    return result;
};

template<typename ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& _factor)
{
    if (this->size != _factor.GetSize())
        throw Exception("Not correct size of adding vector!");

    TVector<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < this->elem[i].GetSize(); j++)
            result[i] += this->elem[i][j] * _factor[i + j];

    return result;
};

template<typename ValType>
bool TMatrix<ValType>::operator==(const TMatrix& _matrix) const
{
    return TVector<TVector<ValType> >::operator==(_matrix);
};

template<typename ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& _matrix) const
{
    return TVector<TVector<ValType> >::operator!=(_matrix);
};

template<typename ValType>
istream& operator>>(istream& _in, TMatrix<ValType>& _matrix)
{
    for (int i = 0; i < _matrix.size; i++)
        _in >> _matrix.elem[i];

    return _in;
};

template<typename ValType>
ostream& operator<<(ostream& _out, const TMatrix<ValType>& _matrix)
{
    for (int i = 0; i < _matrix.size; i++)
    {
        for (int j = 0; j < i; j++)  // for indentations (tab)
            _out << "\t";

        _out << _matrix.elem[i] << endl;
    }

    return _out;
};

#endif
