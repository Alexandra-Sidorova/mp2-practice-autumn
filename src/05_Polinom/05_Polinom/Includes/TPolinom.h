#ifndef _TPOLINOM_H_
#define _TPOLINOM_H_

#include <cstring>
#include <iostream>

#include "TList_TPolinom.h"
#include "TNode_TMonom.h"
#include "exceptions.h"

using namespace std;

enum Variables {x, y, z};

class TPolinom
{
private:
	TList<int, float>* monoms;

	void CastToDefault();
	bool IsOperation(const char) const;
public:
	TPolinom();
	TPolinom(const string);  // TODO
	TPolinom(TList<int, float>*);
	TPolinom(const TPolinom&);
	~TPolinom();

	const TPolinom& operator=(const TPolinom&);
	TPolinom operator+(const TPolinom&);
	TPolinom operator-(const TPolinom&);
	TPolinom operator*(const TPolinom&);
	TPolinom operator-();
	friend ostream& operator<<(ostream&, TPolinom&);
};
//-----------------------------------------------------------------

TPolinom::TPolinom()
{
	monoms = new TList<int, float>();
};

TPolinom::TPolinom(const string _str)  // TODO
{
	if (!_str.length())
		throw Exception("Error! String is empty!");

	monoms = new TList<int, float>;
	
	int i = 0; // number of symbol
	bool ismin = false;  // check for minus

	while (i < _str.length())
	{
		float coeff = 0;
		int degree = 0;
		bool point = false;  // check for floating point
		bool isdegree = false;  // check for degree
		bool isx = false;  // check for x
		bool isy = false;  // check for y
		bool isz = false;  // check for z

		do
		{
			char symbol = static_cast<char>(_str[i]);

			if (isspace(symbol))  // space processing
			{
				i++;
				continue;
			}

			if (isdigit(symbol) && !point && !isdegree)
			{
				coeff = coeff * 10 + (int)symbol - 48;  // ASCII
				i++;
				continue;
			}

			if (isdigit(symbol) && point && !isdegree)
			{
				coeff = coeff + ((int)symbol - 48) * 0.1;  // ASCII
				i++;
				continue;
			}

			if (symbol == 'x')
			{
				isx = true;
				isy = false;
				isz = false;
				isdegree = false;
				i++;
				continue;
			}

			if (symbol == 'y')
			{
				isx = false;
				isy = true;
				isz = false;
				isdegree = false;
				i++;
				continue;
			}

			if (symbol == 'z')
			{
				isx = false;
				isy = false;
				isz = true;
				isdegree = false;
				i++;
				continue;
			}

			if (symbol == '^')
			{
				isdegree = true;
				i++;
				continue;
			}

			if (isdegree)
			{
				if (isx)
					degree = degree + ((int)symbol - 48) * 100;
				if (isy)
					degree = degree + ((int)symbol - 48) * 10;
				if (isz)
					degree = degree + ((int)symbol - 48);

				isx = isy = isz = false;
				i++;
				continue;
			}
		} while (!IsOperation(static_cast<char>(_str[i])) && (i != _str.length()));

		if (ismin && coeff != 0)
			monoms->PushEnd(degree, -coeff);
		if (!ismin && coeff != 0)
			monoms->PushEnd(degree, coeff);

		if (static_cast<char>(_str[i]) == '-')
			ismin = true;
		else
			ismin = false;

		i++;
	}

	this->CastToDefault();
};

TPolinom::TPolinom(TList<int, float>* _monoms)
{
	while (!_monoms->IsEnded())
	{
		if (_monoms->GetpCurrent()->key > 999)
			throw Exception("Error! Degree of monom is not correct!");
		_monoms->Next();
	}

	monoms = new TList<int, float>(*_monoms);
	this->CastToDefault();
};

TPolinom::TPolinom(const TPolinom& _copy)
{
	monoms = new TList<int, float>(*_copy.monoms);
	this->CastToDefault();
};

TPolinom::~TPolinom()
{
	delete monoms;
};
//-----------------------------------------------------------------

void TPolinom::CastToDefault()
{
	if (!monoms)
		throw Exception("Error! Polinom is empty!");

	monoms->SortKey();
};

bool TPolinom::IsOperation(const char _s) const
{
	return (_s == '+' || _s == '-');
};
//-----------------------------------------------------------------

const TPolinom& TPolinom::operator=(const TPolinom& _copy)
{
	if (this == &_copy)
		return *this;

	if (monoms->GetpFirst())
		delete monoms;
	monoms = new TList<int, float>(*_copy.monoms);
};

TPolinom TPolinom::operator+(const TPolinom& _copy)
{
	TPolinom tmp(this->monoms);
	_copy.monoms->Reset();

	while (!_copy.monoms->IsEnded())
	{
		tmp.monoms->Reset();

		while ((!tmp.monoms->IsEnded()) && (_copy.monoms->GetpCurrent()->key != tmp.monoms->GetpCurrent()->key))
			tmp.monoms->Next();

		if (tmp.monoms->IsEnded())
		{
			tmp.monoms->PushEnd(_copy.monoms->GetpCurrent()->key, _copy.monoms->GetpCurrent()->pData);
			_copy.monoms->Next();
			continue;
		}

		tmp.monoms->GetpCurrent()->pData += _copy.monoms->GetpCurrent()->pData;
		_copy.monoms->Next();
	}

	tmp.CastToDefault();

	return tmp;
};

ostream& operator<<(ostream& _out, TPolinom& _p)
{
	_p.monoms->Reset();

	if (_p.monoms->IsEnded())
	{
		_out << "Polinom is empty!" << endl;
		return _out;
	}

	_out << _p.monoms->GetpCurrent()->pData;

	if (_p.monoms->GetpCurrent()->key / 100 != 0)
		_out << "x^(" << int(_p.monoms->GetpCurrent()->key / 100) << ")";
	if (((int)_p.monoms->GetpCurrent()->key / 10) % 10 != 0)
		_out << "y^(" << int(((int)_p.monoms->GetpCurrent()->key / 10) % 10) << ")";
	if ((int)_p.monoms->GetpCurrent()->key % 10 != 0)
		_out << "z^(" << int((int)_p.monoms->GetpCurrent()->key % 10) << ")";

	_p.monoms->Next();

	while (!_p.monoms->IsEnded())
	{
		if (_p.monoms->GetpCurrent()->pData > 0)
			_out << " + " << _p.monoms->GetpCurrent()->pData;
		if (_p.monoms->GetpCurrent()->pData < 0)
			_out << " - " << abs(_p.monoms->GetpCurrent()->pData);
		
		if (_p.monoms->GetpCurrent()->key / 100 != 0)
			_out << "x^(" << int(_p.monoms->GetpCurrent()->key / 100) << ")";
		if (((int)_p.monoms->GetpCurrent()->key / 10) % 10 != 0)
			_out << "y^(" << int(((int)_p.monoms->GetpCurrent()->key / 10) % 10) << ")";
		if ((int)_p.monoms->GetpCurrent()->key % 10 != 0)
			_out << "z^(" << int((int)_p.monoms->GetpCurrent()->key % 10) << ")";

		_p.monoms->Next();
	}

	_out << endl;

	return _out;
};

#endif