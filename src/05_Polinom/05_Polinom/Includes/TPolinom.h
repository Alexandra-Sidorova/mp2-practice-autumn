#ifndef _TPOLINOM_H_
#define _TPOLINOM_H_

#include <cstring>

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

	monoms = new TList<int, float>();
	TNode<int, float>* monom = new TNode<int, float>;

	float coeff = 0;
	int degree = 0;
	bool point = 0;  // check for floating point

	for (int i = 0; i < _str.length(); i++)
	{
		char symbol = static_cast<char>(_str[i]);
		
		if (isspace(symbol))  // space processing
			continue;

		if (isdigit(symbol) && !point)
		{
			coeff = coeff * 10 + (int)symbol - 48;  // ASCII
			continue;
		}

		if (isdigit(symbol) && point)
		{
			coeff = coeff + ((int)symbol - 48) * 0.1;  // ASCII
			continue;
		}




	}
};

TPolinom::TPolinom(TList<int, float>* _monoms)
{
	while (!_monoms->IsEnded())
	{
		if (_monoms->GetpCurrent.key > 999)
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
	delete[] monoms;
};
//-----------------------------------------------------------------

void TPolinom::CastToDefault()
{
	if (!monoms)
		throw Exception("Error! Polinom is empty!");

	monoms->SortData();
}
//-----------------------------------------------------------------


#endif