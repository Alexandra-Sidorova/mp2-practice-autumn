#include "DHeap.h"
#include "exceptions.h"

#include <cmath>

template<typename T>
DHeap<T>::DHeap(int _maxSize, int _currentSize, int _d, T* _elems)
{
	if (_maxSize <= 0 || _currentSize < 0 || _d <= 0 || _elems == NULL)
		throw Exception("[Error] Incorrect data!");

	maxSize = _maxSize;
	currentSize = _currentSize;
	d = _d;
	
	elems = new T[maxSize];
	for (int i = 0; i < currentSize; i++)
		elems[i] = _elems[i];
};

template<typename T>
DHeap<T>::DHeap(const DHeap& _copy)
{
	maxSize = _copy.maxSize;
	currentSize = _copy.currentSize;
	d = _copy.d;
	
	elems = new T[maxSize];
	for (int i = 0; i < currentSize; i++)
		elems[i] = _copy.elems[i];
};


template<typename T>
DHeap<T>::~DHeap()
{
	maxSize = currentSize = d = 0;
	delete elems;
};
//-----------------------------------------------------------------------------------

template<typename T>
int DHeap<T>::MinChild(int i)
{
	if (i < 0 || i > currentSize)
		throw Exception("[Error] Incorrent ID parent!");

	if (i * d >= currentSize)
		return (-1);  // have no childs;

	int childFirst = i * d + 1;
	int childLast = std::min(i * d + d, currentSize - 1);
	int childMin = childFirst;

	for (int j = childFirst + 1; j < childLast; j++)
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
		throw Exception("[Error] Incorrect ID elements to transpose!");

	T tmp = elems[i];
	elems[i] = elems[j];
	elems[j] = tmp;
};

template<typename T>
void DHeap<T>::SiftUp(int i)
{
	if (i < 0 || i > currentSize)
		throw Exception("[Error] Incorrent ID element!");

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
		throw Exception("[Error] Incorrent ID element!");

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
void DHeap<T>::Heapify()
{
	for (int i = currentSize - 1; i >= 0; i--)
		SiftDown(i);
};