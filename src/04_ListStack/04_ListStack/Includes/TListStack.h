#ifndef _TLISTSTACK_H_
#define _TLISTSTACK_H_

#include "exceptions.h"
#include "TList.h"
#include "TStack.h"

using namespace std;

template<typename ValType>
class TListStack : TStack<ValType>
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
	return (elem->pFirst == NULL);
};

template<typename ValType>
bool TListStack<ValType>::IsFull() const
{
	//todo
};
//----------------------------------------------------

template<typename ValType>
void TListStack<ValType>::Push(ValType _elem)
{
	if (IsFull())
		throw Exception("Error: stack is full!");

	elem->PopBegin(_elem, NULL);
};

template<typename ValType>
void TListStack<ValType>::Pop()
{
	if (IsEmpty())
		throw Exception("Error: stack is empty!");

	elem->Delete(elem->pFirst->key);
};

template<typename ValType>
ValType TListStack<ValType>::TopWatch() const
{
	if (IsEmpty())
		throw Exception("Error: stack is empty!");

	return elem->pFirst->key;
}

#endif