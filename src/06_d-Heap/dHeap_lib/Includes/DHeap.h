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
	DHeap(int, int);
	DHeap(int, int, int, T*);
	DHeap(const DHeap&);
	~DHeap();

	int GetCurrentSize() const;
	T* GetElems() const;
	void SetCurrentSize(const int);

	void Push(const T);
	int MinChild(int) const;
	void Transpose(int, int);
	void SiftUp(int);
	void SiftDown(int);
	void PopMin();
	T WatchMin() const;
	void Heapify();
};

#endif