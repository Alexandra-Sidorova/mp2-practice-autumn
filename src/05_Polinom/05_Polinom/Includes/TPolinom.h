#ifndef _TPOLINOM_H_
#define _TPOLINOM_H_

#include <cstring>
#include <iostream>

#include "TList_TPolinom.h"
#include "TNode_TMonom.h"
#include "exceptions.h"

using namespace std;

class TPolinom
{
private:
	TList<int, float>* monoms;

	void CastToDefault();
	bool IsOperation(const char) const;
public:
	TPolinom();
	TPolinom(const string);
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

TPolinom::TPolinom(const string _str)
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
		bool iscoeff = true;  // check for coeff
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

			if (symbol == '.')
			{
				point = true;
				i++;
				continue;
			}

			if (isdigit(symbol) && iscoeff && !point && !isdegree)
			{
				coeff = coeff * 10 + (int)symbol - 48;  // ASCII
				i++;
				continue;
			}

			if (isdigit(symbol) && iscoeff && point && !isdegree)
			{
				int tmp = (int)coeff;
				float tmpcoeff = coeff;
				float ex = ((int)symbol - 48) / 10.;  // ASCII

				while (tmp != tmpcoeff)
				{
					ex /= 10.;
					tmpcoeff *= 10.;
					tmp = (int)tmpcoeff;
				}

				coeff = coeff + ex;
				i++;
				continue;
			}

			if (symbol == 'x')
			{
				isx = true;
				isy = false;
				isz = false;
				isdegree = false;
				iscoeff = false;
				point = false;
				i++;
				continue;
			}

			if (symbol == 'y')
			{
				isx = false;
				isy = true;
				isz = false;
				isdegree = false;
				iscoeff = false;
				point = false;
				i++;
				continue;
			}

			if (symbol == 'z')
			{
				isx = false;
				isy = false;
				isz = true;
				isdegree = false;
				iscoeff = false;
				point = false;
				i++;
				continue;
			}

			if (symbol == '^' && (isx || isy || isz))
			{
				isdegree = true;
				i++;
				continue;
			}

			if (isdegree && (isx || isy || isz))
			{
				if (isx)
					degree = degree + ((int)symbol - 48) * 100;
				if (isy)
					degree = degree + ((int)symbol - 48) * 10;
				if (isz)
					degree = degree + ((int)symbol - 48);

				isx = isy = isz = false;
				isdegree = false;
				i++;
				continue;
			}

			throw Exception("Error! Not correct string!");

		} while (!IsOperation(static_cast<char>(_str[i])) && (i != _str.length()));

		if (ismin && (coeff != 0))
			monoms->PushEnd(degree, -coeff);
		if (!ismin && (coeff != 0))
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
	return *this;
};

TPolinom TPolinom::operator+(const TPolinom& _copy)
{
	TPolinom tmp(*this);
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
	
	tmp.monoms->Reset();
	while (!tmp.monoms->IsEnded())
	{
		if (tmp.monoms->GetpCurrent()->pData == 0)
		{
			tmp.monoms->Delete(tmp.monoms->GetpCurrent()->key);
			continue;
		}

		tmp.monoms->Next();
	}

	_copy.monoms->Reset();
	tmp.monoms->Reset();
	tmp.CastToDefault();
	return tmp;
};

TPolinom TPolinom::operator-(const TPolinom& _copy)
{
	TPolinom tmp(_copy);
	return *this + (-tmp);
};

TPolinom TPolinom::operator*(const TPolinom& _copy)
{
	TPolinom tmp;
	_copy.monoms->Reset();

	while (!_copy.monoms->IsEnded())
	{
		this->monoms->Reset();

		while (!this->monoms->IsEnded())
		{
			float coeff = this->monoms->GetpCurrent()->pData * _copy.monoms->GetpCurrent()->pData;

			int degreeX = this->monoms->GetpCurrent()->key / 100;
			int degreeY = (this->monoms->GetpCurrent()->key / 10) % 10;
			int degreeZ = this->monoms->GetpCurrent()->key % 10;

			int copyDegreeX = _copy.monoms->GetpCurrent()->key / 100;
			int copyDegreeY = (_copy.monoms->GetpCurrent()->key / 10) % 10;
			int copyDegreeZ = _copy.monoms->GetpCurrent()->key % 10;
			
			if (((degreeX + copyDegreeX) > 9) || ((degreeY + copyDegreeY) > 9)
				|| ((degreeZ + copyDegreeZ) > 9))
				throw Exception("Error! Degrees are not correct!");

			int key = (degreeX + copyDegreeX) * 100 +
				(degreeY + copyDegreeY) * 10 + (degreeZ + copyDegreeZ);

			tmp.monoms->PushEnd(key, coeff);
			this->monoms->Next();
		}

		_copy.monoms->Next();
	}

	this->monoms->Reset();
	_copy.monoms->Reset();
	tmp.monoms->Reset();
	tmp.CastToDefault();
	return tmp;
};

TPolinom TPolinom::operator-()
{
	TPolinom tmp(*this);

	while (!tmp.monoms->IsEnded())
	{
		tmp.monoms->GetpCurrent()->pData *= -1;
		tmp.monoms->Next();
	}

	tmp.monoms->Reset();
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