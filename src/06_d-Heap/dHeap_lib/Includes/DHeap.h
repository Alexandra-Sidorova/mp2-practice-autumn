#ifndef _DHEAP_H_
#define _DHEAP_H_

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

	int MinChild(int);
	void Transpose(int, int);
	void SiftUp(int);
	void SiftDown(int);
	void PopMin();
	void Heapify();
};

#endif