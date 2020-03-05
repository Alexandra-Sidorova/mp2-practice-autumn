#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

#include "DHeap.h"

#define D 3

template<typename T>
class HeapSort
{
public:
	static void Sort(T*, int);
};
//------------------------------------------------------

template<typename T>
void HeapSort<T>::Sort(T* _array, int _size)
{
	if (_array == nullptr || _size == 0)
		throw Exception("Array is empty!");
	if (_size < 0)
		throw Exception("Incorrect size!");

	DHeap<T> heap(_size, _size, D, _array);
	heap.Heapify();

	for (int i = _size - 1; i >= 0; i--)
	{
		heap.Transpose(0, heap.GetCurrentSize() - 1);
		heap.SetCurrentSize(heap.GetCurrentSize() - 1);
		heap.SiftDown(0);
	}
};

#endif