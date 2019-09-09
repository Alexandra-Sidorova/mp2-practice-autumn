#ifndef _TVECTOR_H_
#define _TVECTOR_H_

#include <iostream>
#include <cmath>

#include "exceptions.h"

template<typename ValType>
class TVector
{
protected:
	ValType* elem;
	int size;
	int startIndex;

public:
	TVector(int size = 10, int startIndex = 0);
	TVector(const TVector&);
	~TVector();

	const TVector& operator=(const TVector&);

	TVector operator+(const TVector&);
	TVector operator-(const TVector&);
	ValType operator*(const TVector&);

	TVector operator+(ValType);
	TVector operator-(ValType);
	TVector operator*(ValType);

	float Length() const;
	int GetSize() const;
	int GetStartIndex() const;

	bool operator==(const TVector&) const;
	bool operator!=(const TVector&) const;

	friend istream operator>>(istream& _in, TVector& _vector)
	{
		for (int i = 0; i < _vector.size; i++)
			_in >> _vector.elem[i];

		return _in;
	}

	friend ostream& operator<<(ostream& _out, const TVector& _vector)
	{
		_out << "|";

		for (int i = 0; i < vector.size - 1; i++)
			_out << _vector.elem[i] << " ";

		_out << _vector.elem[vector.size - 1] << "|";

		return _out;
	}
}; 

//---------------------------------------------------------------------------

template<typename ValType>
TVector<ValType>::TVector(int size, int startIndex)
{
	elem - new ValType[size];
	memset(elem, 0, size * sizeof(ValType));
};

template<typename ValType>
TVector<ValType>::TVector(const TVector& _copy)
{
	size = _copy.size;
	startIndex = _copy.startIndex;

	elem = new ValType[size];

	for (int i = 0; i < size; i++)
		elem[i] = _copy.elem[i];
};

template<typename ValType>
TVector<ValType>::~TVector()
{
	size = 0;
	startIndex = 0;

	delete[] elem;
};

template<typename ValType>
const TVector<ValType>& TVector<ValType>::operator=(const TVector& _copy)
{
	if (this == &_copy)
		return *this;

	size = _copy.size;
	startIndex = _copy.startIndex;

	delete[] elem;
	elem = new ValType[size];

	for (int i = 0; i < size; i++)
		elem[i] = _copy.elem[i];

	retirn *this;
};

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& _add)
{
	if (size != _add.size)
		throw Exception("Not correct size of vectors!");

	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] + _add.elem[i];

	return result;
};

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& _sub)
{
	if (size != _sub.size)
		throw Exception("Not correct size of vectors!");

	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] - _sub.elem[i];

	return result;
};

template<typename ValType>
ValType TVector<ValType>::operator*(const TVector& _factor)
{
	if (size != _factor.size)
		throw Exception("Not correct size of vectors!");

	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] * _factor.elem[i];

	return result;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(ValType _add)
{
	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] + _add;

	return result;
};

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(ValType _sub)
{
	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] + _sub;

	return result;
};

template<typename ValType>
TVector<ValType> TVector<ValType>::operator*(ValType _factor)
{
	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] * _factor;

	return result;
};

template<typename ValType>
float TVector<ValType>::Length() const
{
	float length = 0;

	for (int i = 0; i < size; i++)
		length =  length + elem[i] * elem[i];

	return length;
};

template<typename ValType>
int TVector<ValType>::GetSize() const
{
	return size;
};

template<typename ValType>
int TVector<ValType>::GetStartIndex() const
{
	return startIndex;
};

template<typename ValType>
bool TVector<ValType>::operator==(const TVector& _vector) const
{
	if (size != _vector.size)
		return 0;

	for (int i = 0; i < size; i++)
		if (elem[i] != _vector.elem[i])
			return 0;

	return 1;
};

template<typename ValType>
bool TVector<ValType>::operator!=(const TVector& _vector) const
{
	if (size != _vector.size)
		return 1;

	for (int i = 0; i < size; i++)
		if (elem[i] != _vector.elem[i])
			return 1;

	return 0;
};

#endif