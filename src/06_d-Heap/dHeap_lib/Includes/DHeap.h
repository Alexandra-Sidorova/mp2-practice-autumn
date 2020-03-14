#ifndef _DHEAP_H_
#define _DHEAP_H_

#include "exceptions.h"

#include <cmath>
#include <algorithm>

template<typename T>
class DHeap
{
private:
	int maxSize;
	int currentSize;
	int d;
	T* elems;

public:
	DHeap(int, int, int, T*);
	DHeap(const DHeap&);
	~DHeap();

	int GetCurrentSize() const;

	void Push(const T);
	int MinChild(int) const;
	void Transpose(int, int);
	void SiftUp(int);
	void SiftDown(int);
	void PopMin();
	T WatchMin() const;
	void Heapify();
};
//-----------------------------------------------------------------------------------

template<typename T>
DHeap<T>::DHeap(int _maxSize, int _currentSize, int _d, T* _elems)
{
	if (_maxSize < 0 || _currentSize < 0 || _d <= 0 || _elems == nullptr || _currentSize > _maxSize)
		throw Exception("Incorrect data for create DHeap!");

	maxSize = _maxSize;
	currentSize = _currentSize;
	d = _d;
	elems = _elems;
};

template<typename T>
DHeap<T>::DHeap(const DHeap<T>& _copy)
{
	maxSize = _copy.maxSize;
	currentSize = _copy.currentSize;
	d = _copy.d;
	elems = _copy.elems;
};

template<typename T>
DHeap<T>::~DHeap()
{
	maxSize = currentSize = d = 0;
	elems = nullptr;
};
//-----------------------------------------------------------------------------------

template<typename T>
int DHeap<T>::GetCurrentSize() const
{
	return currentSize;
};

template<typename T>
void DHeap<T>::Push(const T _elem)
{
	elems[currentSize++] = _elem;
	Heapify();
};

template<typename T>
int DHeap<T>::MinChild(int i) const
{
	if (i < 0 || i > currentSize)
		throw Exception("Incorrent ID parent!");

	if (i * d + 1 >= currentSize)
		return (-1);  // have no childs;

	int childFirst = i * d + 1;
	int childLast = min(i * d + d, currentSize - 1);
	int childMin = childFirst;

	for (int j = childFirst; j <= childLast; j++)
	{
		if (elems[childMin] > elems[j])
			childMin = j;
	}

	return childMin;
};

template<typename T>
void DHeap<T>::Transpose(int i, int j)
{
	if (i < 0 || j < 0 || i > currentSize || j > currentSize)
		throw Exception("Incorrect ID elements to transpose!");

	T tmp = elems[i];
	elems[i] = elems[j];
	elems[j] = tmp;
};

template<typename T>
void DHeap<T>::SiftUp(int i)
{
	if (i < 0 || i > currentSize)
		throw Exception("Incorrent ID element!");

	int parent = (i - 1) / d;

	while (i > 0)
	{
		if (elems[parent] > elems[i])
		{
			Transpose(parent, i);
			i = parent;
		}
		else break;
	}
};

template<typename T>
void DHeap<T>::SiftDown(int i)
{
	if (i < 0 || i > currentSize)
		throw Exception("Incorrent ID element!");

	int childMin = MinChild(i);

	while ((childMin != -1) && (elems[childMin] < elems[i]))
	{
		Transpose(childMin, i);
		i = childMin;
		childMin = MinChild(i);
	}
};

template<typename T>
void DHeap<T>::PopMin()
{
	Transpose(0, currentSize - 1);
	currentSize--;
	SiftDown(0);
};

template<typename T>
T DHeap<T>::WatchMin() const
{
	return elems[0];
};

template<typename T>
void DHeap<T>::Heapify()
{
	for (int i = currentSize - 1; i >= 0; i--)
		SiftDown(i);
};

#endif