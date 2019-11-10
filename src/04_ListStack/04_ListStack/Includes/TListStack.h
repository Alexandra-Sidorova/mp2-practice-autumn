#ifndef _TLISTSTACK_H_
#define _TLISTSTACK_H_

#include "exceptions.h"
#include "TList.h"
#include "TStack.h"

using namespace std;

template<typename ValType>
class TListStack : public TStack<ValType>
{
private:
	TList<ValType, ValType>* elem;

public:
	TListStack();
	TListStack(const TListStack&);
	~TListStack();

	bool IsEmpty() const;
	bool IsFull() const;

	void Push(ValType);
	void Pop();
	ValType TopWatch() const;
};
//----------------------------------------------------

template<typename ValType>
TListStack<ValType>::TListStack()
{
	elem = new TList<ValType, ValType>;
};

template<typename ValType>
TListStack<ValType>::TListStack(const TListStack& _copy)
{
	elem = _copy.elem;
};

template<typename ValType>
TListStack<ValType>::~TListStack()
{
	delete[] elem;
};
//----------------------------------------------------

template<typename ValType>
bool TListStack<ValType>::IsEmpty() const
{
	return (elem->GetpFirst() == NULL);
};

template<typename ValType>
bool TListStack<ValType>::IsFull() const
{
	TList<ValType, ValType> listCheck(this->elem->GetpFirst());

	int size = 0, checkSize = 0;

	while (!listCheck.IsEnded())
	{
		listCheck.Next();
		size++;
	}

	listCheck.PopEnd(0, NULL);
	listCheck.Reset();

	while (!listCheck.IsEnded())
	{
		listCheck.Next();
		checkSize++;
	}

	if (checkSize == (size + 1))
		return false;

	return true;
};
//----------------------------------------------------

template<typename ValType>
void TListStack<ValType>::Push(ValType _elem)
{
	if (IsFull())
		throw Exception("Error: stack is full!");

	elem->PopBegin(_elem, NULL);
	elem->Reset();
};

template<typename ValType>
void TListStack<ValType>::Pop()
{
	if (IsEmpty())
		throw Exception("Error: stack is empty!");

	elem->Delete(elem->GetpFirst()->key);
	elem->Reset();
};

template<typename ValType>
ValType TListStack<ValType>::TopWatch() const
{
	if (IsEmpty())
		throw Exception("Error: stack is empty!");

	return elem->GetpFirst()->key;
}

#endif