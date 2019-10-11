#ifndef _TQUEUE_H_
#define _TQUEUE_H_

#include "Exceptions.h"

template<typename ValType>
class TQueue
{
private:
	ValType* elem;
	int size;
	int count;
	int lowIndex;
	int highIndex;

	int GetNextIndex(int);
public:
	TQueue(int);
	TQueue(const TQueue<ValType>&);
	~TQueue();

	void Push(ValType);
	ValType Pop();

	bool IsFull() const;
	bool IsEmpty() const;

};

template<typename ValType>
int TQueue<ValType>::GetNextIndex(int _index)
{
	return ((++index) % size);
};

template<typename ValType>
TQueue<ValType>::TQueue(int _size)
{
	if (_size <= 0)
		throw Exception("Error: not correct size of queue!");

	size = _size;
	count = lowIndex = highIndex = 0;
	
	elem = new ValType(size);
	memset(elem, 0, sizeof(ValType) * size);
};

template<typename ValType>
TQueue<ValType>::TQueue(const TQueue<ValType>& _copy)
{
	size = _copy.size;
	count = _copy.count;
	lowIndex = _copy.lowIndex;
	hightIndex = _copy.highIndex;

	elem = new ValType(size);
	memcpy(elem, _copy.elem, sizeof(ValType) * size);
};

template<typename ValType>
TQueue<ValType>::~TQueue()
{
	size = count = lowIndex = highIndex = 0;
	delete[] elem;
};

template<typename ValType>
void TQueue<ValType>::Push(ValType _item)
{
	if (IsFull())
		throw Exception("Error: Queue is full!");

	elem[GetNextIndex(highIndex)] = _item;
	count++;
};

template<typename ValType>
ValType TQueue<ValType>::Pop()
{
	if (IsEmpty())
		throw Exception("Error: Queue is empty!");

	count--;
	return elem[GetNextIndex(lowIndex) - 1];
};

#endif
