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

    ValType Determinant() const;

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
ValType TMatrix<ValType>::Determinant() const
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
    if (this == &_copy)
        return *this;

    if (this->size != _copy.size)
    {
        this->size = _copy.size;

        delete[] this->elem;
        this->elem = new TVector<ValType>[_copy.size];
    }

    for (int i = 0; i < this->size; i++)
        this->elem[i] = _copy.elem[i];

    return *this;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& _add)
{
    if (this->size != _add.size)
        throw Exception("Not correct size of adding matrix!");
    
    TMatrix<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        result.elem[i] = this->elem[i] + _add.elem[i];

    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& _sub)
{
    if (this->size != _sub.size)
        throw Exception("Not correct size of adding matrix!");

    TMatrix<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        result.elem[i] = this->elem[i] - _sub.elem[i];

    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& _factor)
{
    if (this->size != _factor.size)
        throw Exception("Not correct size of adding matrix!");

    TMatrix<ValType> result(this->size);

    for (int i = 0; i < this->size; i++)
        for (int j = this->elem[i].GetStartIndex(); j < this->size; j++)
            for (int k = i; k <= j; k++)
                result.elem[i][j - i] += this->elem[i][k - i] * _factor.elem[k][j - k];
        
    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(ValType _add)
{
    TMatrix<ValType> result(*this);

    for (int i = 0; i < this->size; i++)
        result[i] = result.elem[i] + _add;

    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(ValType _sub)
{
    TMatrix<ValType> result(*this);

    for (int i = 0; i < this->size; i++)
        result[i] = result.elem[i] - _sub;

    return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType _factor)
{
    TMatrix<ValType> result(*this);

    for (int i = 0; i < this->size; i++)
        result[i] = result.elem[i] * _factor;

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
    if (this->size != _matrix.size)
        return false;

    for (int i = 0; i < this->size; i++)
        if (this->elem[i] != _matrix.elem[i])
            return false;

    return true;
};

template<typename ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& _matrix) const
{
    return !(*this == _matrix);
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