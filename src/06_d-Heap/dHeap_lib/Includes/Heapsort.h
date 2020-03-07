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

	for (int i = 0; i < _size; i++)
		heap.PopMin();
};

#endif