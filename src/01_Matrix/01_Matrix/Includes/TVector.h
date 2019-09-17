#ifndef _TVECTOR_H_
#define _TVECTOR_H_

#include <iostream>
#include <cmath>

#include "exceptions.h"

using namespace std;

template<class ValType>
class TVector
{
protected:
	ValType* elem;
	int size;
	int startIndex;

public:
	TVector(int _size = 10, int _startIndex = 0);
	TVector(const TVector&);
	virtual ~TVector();

	const TVector& operator=(const TVector&);

	ValType& operator[](int);
	const ValType& operator[](int) const;

	TVector operator+(const TVector&);
	TVector operator-(const TVector&);
	ValType operator*(const TVector&);  // scalar

	TVector operator+(ValType);
	TVector operator-(ValType);
	TVector operator*(ValType);

	float Length() const;
	int GetSize() const;
	int GetStartIndex() const;

	bool operator==(const TVector&) const;
	bool operator!=(const TVector&) const;

	template<typename ValType> friend istream& operator>>(istream&, TVector<ValType>&);
	template<typename ValType> friend ostream& operator<<(ostream&, const TVector<ValType>&);
}; 

//---------------------------------------------------------------------------

template<class ValType>
TVector<ValType>::TVector(int _size, int _startIndex)
{
	if (_size < 0)
		throw Exception("Not correct size of vector!");

	if (_startIndex < 0)
		throw Exception("Not correct starting index of vector!");

	size = _size;
	startIndex = _startIndex;

	if (size == 0)
		elem = NULL;
	else
	{
		elem = new ValType[size];
		for (int i = 0; i < size; i++)
			elem[i] = 0;
	}
};

template<class ValType>
TVector<ValType>::TVector(const TVector& _copy)
{
	size = _copy.size;
	startIndex = _copy.startIndex;

	if (size == 0)
		elem = NULL;
	else
	{
		elem = new ValType[size];
		for (int i = 0; i < size; i++)
			elem[i] = _copy.elem[i];
	}
};

template<class ValType>
TVector<ValType>::~TVector()
{
	size = 0;
	startIndex = 0;

	delete[] elem;
	elem = NULL;
};

template<class ValType>
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

	return *this;
};

template<class ValType>
ValType& TVector<ValType>::operator[](int _index)
{
	if ((_index < 0) || (_index >= size))
		throw Exception("Not correct index of vector!");

	return elem[_index];
};

template<class ValType>
const ValType& TVector<ValType>::operator[](int _index) const
{
	if ((_index < 0) || (_index >= size))
		throw Exception("Not correct index of vector!");

	return elem[_index];
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& _add)
{
	if (size != _add.size)
		throw Exception("Not correct size of vectors!");

	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] + _add.elem[i];

	return result;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& _sub)
{
	if (size != _sub.size)
		throw Exception("Not correct size of vectors!");

	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] - _sub.elem[i];

	return result;
};

template<class ValType>
ValType TVector<ValType>::operator*(const TVector& _factor)
{
	if (size != _factor.size)
		throw Exception("Not correct size of vectors!");

	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] * _factor.elem[i];

	return result;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(ValType _add)
{
	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] + _add;

	return result;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(ValType _sub)
{
	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] + _sub;

	return result;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator*(ValType _factor)
{
	TVector<ValType> result(size, startIndex);

	for (int i = 0; i < size; i++)
		result.elem[i] = elem[i] * _factor;

	return result;
};

template<class ValType>
float TVector<ValType>::Length() const
{
	float length = 0;

	for (int i = 0; i < size; i++)
		length =  length + elem[i] * elem[i];

	return length;
};

template<class ValType>
int TVector<ValType>::GetSize() const
{
	return size;
};

template<class ValType>
int TVector<ValType>::GetStartIndex() const
{
	return startIndex;
};

template<class ValType>
bool TVector<ValType>::operator==(const TVector& _vector) const
{
	if (size != _vector.size)
		return 0;

	for (int i = 0; i < size; i++)
		if (elem[i] != _vector.elem[i])
			return 0;

	return 1;
};

template<class ValType>
bool TVector<ValType>::operator!=(const TVector& _vector) const
{
	if (size != _vector.size)
		return 1;

	for (int i = 0; i < size; i++)
		if (elem[i] != _vector.elem[i])
			return 1;

	return 0;
};

template<class ValType>
istream& operator>>(istream& _in, TVector<ValType>& _vector)
{
	for (int i = 0; i < _vector.size; i++)
		_in >> _vector.elem[i];

	return _in;
};

template<class ValType>
ostream& operator<<(ostream& _out, const TVector<ValType>& _vector)
{
	for (int i = 0; i < _vector.size; i++)
		_out << _vector.elem[i] << "\t";

	return _out;
};

#endif