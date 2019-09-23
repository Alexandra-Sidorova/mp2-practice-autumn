#ifndef _TSTACK_H_
#define _TSTACK_H

#include "exceptions.h"

using namespace std;

template<typename ValType>
class TStack
{
private:
	int size;
	int top;
	ValType* elem;
public:
	TStack(int);
	TStack(const TStack<ValType>&);
	~TStack();

	bool IsEmpty() const;
	bool IsFull() const;

	void Push(ValType);
	ValType Pop();
	ValType TopWatch();

	int GetSize() const;
};

//----------------------------------------------------

template<typename ValType>
TStack<ValType>::TStack(int _size) : size(_size)
{
	if (size < 0)
		throw Exception("Not correct size of stack!");

	elem = new ValType[size];
	memset(elem, 0, sizeof(ValType) * size);

	top = 0;
};

template<typename ValType>
TStack<ValType>::TStack(const TStack<ValType>& _copy) : size(_copy.size), top(_copy.top)
{
	elem = new ValType[size];
	memset(elem, _copy.elem, sizeof(ValType) * size);
};

template<typename ValType>
TStack<ValType>::~TStack()
{
	size = 0;
	top = 0;
	delete[] elem;
};

template<typename ValType>
bool TStack<ValType>::IsEmpty() const
{
	return(top == 0);
};

template<typename ValType>
bool TStack<ValType>::IsFull() const
{
	return(top == size);
};

template<typename ValType>
void TStack<ValType>::Push(ValType _object)
{
	if (IsFull())
		throw Exception("Error: stack is full!");

	elem[top++] = _object;
};

template<typename ValType>
ValType TStack<ValType>::Pop()
{
	if (IsEmpty())
		throw Exception("Error: stack is empty!");

	return (elem[--top]);
};

template<typename ValType>
ValType TStack<ValType>::TopWatch()
{
	if (IsEmpty())
		throw Exception("Error: stack is empty!");

	return (elem[top - 1]);
};

template<typename ValType>
int TStack<ValType>::GetSize() const
{
	return top;
}

#endif