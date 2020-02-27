#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

#include "DHeap.h"

template<typename T>
class HeapSort
{
public:
	static void Sort(T*&, int);
};


template<typename T>
void HeapSort<T>::Sort(T*& _array, int _size)
{
	DHeap<T> heap(_size, _size, 2, _array);
	heap.Heapify();

	for (int i = _size - 1; i >= 0; i--)
	{
		heap.Transpose(0, heap.GetCurrentSize() - 1);
		heap.SetCurrentSize(heap.GetCurrentSize() - 1);
		heap.SiftDown(0);
	}

	for (int i = 0; i < _size; i++)
		_array[i] = heap.GetElems()[i];
};
#endif