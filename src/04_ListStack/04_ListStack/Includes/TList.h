#ifndef _TLIST_H_
#define _TLIST_H_

#include <iostream>

#include "TNode.h"
#include "exceptions.h"

template<typename TKey, class TData>
class TList
{
private:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pCurrent;
	TNode<TKey, TData>* pNext;
	TNode<TKey, TData>* pPrev;

public:
	TList();
	TList(const TList&);
	TList(const TNode<TKey, TData>*);
	~TList();

	void Reset();
	void Next();
	bool IsEnded() const;

	TNode<TKey, TData>* Search(TKey);
	void PopBegin(TKey, TData*);
	void PopEnd(TKey, TData*);
	void PopBefore(TKey, TKey, TData*);
	void PopAfter(TKey, TKey, TData*);
	void Delete(TKey);

	void Print();
};
//-----------------------------------------------------------------

template<typename TKey, class TData>
TList<TKey, TData>::TList()
{
	pFirst = pNext = pPrev = pCurrent = NULL;
};

template<typename TKey, class TData>
TList<TKey, TData>::TList(const TList& _copy)
{
	pNext = pPrev = pCurrent = NULL;

	if (_copy.pFirst == NULL)
	{
		pFirst = NULL;
	}
	else
	{
		pFirst = new TNode<TKey, TData>(*_copy.pFirst);
		pFirst->pNext = NULL;
		pCurrent = pFirst;

		_copy.Reset();

		while (!_copy.IsEnded())
		{
			_copy.Next();

			pCurrent->pNext = new TNode<TKey, TData>(*_copy.pCurrent);

			pPrev = pCurrent;
			pCurrent = pCurrent->pNext;
			pNext = pCurrent->pNext = NULL;
		}
	}
};

template<typename TKey, class TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* _node)
{
	pFirst = pCurrent = _node;
	pPrev = pNext = NULL;
};

template<typename TKey, class TData>
TList<TKey, TData>::~TList()
{
	this->Reset();
	while (!this->IsEnded())
	{
		this->Next();
		delete pPrev;
	}

	delete pCurrent;

	pFirst = pNext = pPrev = pCurrent = NULL;
};
//-----------------------------------------------------------------

template<typename TKey, class TData>
void TList<TKey, TData>::Reset()
{
	pPrev = NULL;
	pCurrent = pFirst;
	pNext = pCurrent->pNext;
};

template<typename TKey, class TData>
void TList<TKey, TData>::Next()
{
	pPrev = pCurrent;
	pCurrent = pNext;

	if (pCurrent)
		pNext = pCurrent->pNext;
	else
		pNext = NULL;
};

template<typename TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
	return (pCurrent == NULL);
};
//-----------------------------------------------------------------

template<typename TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey _key)
{
	this->Reset();

	while (!this->IsEnded())
	{
		if (_key == pCurrent->key)
			return pCurrent;

		this->Next();
	}

	this->Reset();
	return NULL;
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopBegin(TKey _key, TData* _data)
{
	if (!(this->pCurrent == NULL))
		this->Reset();

	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data, pFirst);
	pNext = pFirst;
	pFirst = newNode;
	pCurrent = pFirst;

	this->Reset();
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopEnd(TKey _key, TData* _data)
{
	this->Reset();

	while (pNext)
		this->Next();

	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data);
	pCurrent->pNext = newNode;

	this->Reset();
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopBefore(TKey _superKey, TKey _key, TData* _data)
{
	this->Reset();

	if (this->IsEnded())
	{
		this->PopBegin(_key, _data);
		return;
	}

	TNode<TKey, TData>* nodeFind = Search(_superKey);

	if (nodeFind != NULL)
	{
		TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data, pCurrent);
		pNext = pCurrent;
		pPrev->pNext = newNode;
		pCurrent = newNode;

		this->Reset();
		return;
	}

	this->Reset();
	throw Exception("Error: key didn't find!");
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopAfter(TKey _superKey, TKey _key, TData* _data)
{
	this->Reset();

	TNode<TKey, TData>* nodeFind = Search(_superKey);

	if (nodeFind != NULL)
	{
		TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data, pNext);
		pCurrent->pNext = newNode;
		pPrev = pCurrent;
		pCurrent = newNode;

		this->Reset();
		return;
	}

	this->Reset();
	throw Exception("Error: key didn't find!");
};

template<typename TKey, class TData>
void TList<TKey, TData>::Delete(TKey _key)
{
	this->Reset();

	if (!pFirst)
	{
		this->Reset();
		throw Exception("Error: list is empty!");
	}

	if (pFirst->key == _key)
	{
		delete pFirst;
		pFirst = pNext;
		
		this->Reset();
		return;
	}

	TNode<TKey, TData>* nodeFind = Search(_key);

	if (nodeFind != NULL)
	{
		pPrev->pNext = pNext;
		delete nodeFind;
		
		this->Reset();
		return;
	}

	this->Reset();
	throw Exception("Error: key didn't find!");
};

template<typename TKey, class TData>
void TList<TKey, TData>::Print()
{
	this->Reset();

	while (!this->IsEnded())
	{
		cout << this->pCurrent->key << " ";
		this->Next();
	}
}

#endif