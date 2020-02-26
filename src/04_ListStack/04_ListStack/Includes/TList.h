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
	TNode<TKey, TData>* GetpFirst() const;

	TNode<TKey, TData>* Search(TKey);
	void PopBegin(TKey, TData*);
	void PopEnd(TKey, TData*);
	void PopBefore(TKey, TKey, TData*);
	void PopAfter(TKey, TKey, TData*);
	void Delete(TKey);

	template<typename TKey, class TData> friend ostream& operator<<(ostream&, TList<TKey, TData>&);
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

	if (!_copy.pFirst)
		pFirst = NULL;
	else
	{
		pFirst = new TNode<TKey, TData>(*_copy.pFirst);
		pFirst->pNext = NULL;
		pCurrent = pFirst;

		TNode<TKey, TData>* iter = new TNode<TKey, TData>;
		iter = _copy.pFirst;

		while (iter->pNext)
		{
			iter = iter->pNext;
			pCurrent->pNext = new TNode<TKey, TData>(*iter);

			pPrev = pCurrent;
			pCurrent = pCurrent->pNext;
			pNext = pCurrent->pNext = NULL;
		}

		pPrev = NULL;
		pCurrent = pFirst;
		pNext = pFirst->pNext;
	}
};

template<typename TKey, class TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* _node)
{
	pNext = pPrev = pCurrent = NULL;

	if (!_node)
		pFirst = NULL;
	else
	{
		TNode<TKey, TData>* node = new TNode<TKey, TData>(*_node);
		pFirst = node;

		TNode<TKey, TData>* iter = _node->pNext;
		TNode<TKey, TData>* prev = pFirst;

		while (iter)
		{
			TNode<TKey, TData>* tmp = new TNode<TKey, TData>(*iter);
			prev->pNext = tmp;
			prev = tmp;
			iter = iter->pNext;
		}

		pCurrent = pFirst;
		pNext = pCurrent->pNext;
	}
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
	if (pFirst)
		pNext = pCurrent->pNext;
	else
		pNext = NULL;
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

template<typename TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::GetpFirst() const
{
	return pFirst;
};
//-----------------------------------------------------------------

template<typename TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey _key)
{
	TNode<TKey, TData>* tmppCurrent = pCurrent;
	TNode<TKey, TData>* tmppNext = pNext;
	TNode<TKey, TData>* tmppPrev = pPrev;

	this->Reset();

	while (!this->IsEnded())
	{
		if (_key == pCurrent->key)
		{
			TNode<TKey, TData>* findNode = pCurrent;
			pCurrent = tmppCurrent;
			pNext = tmppNext;
			pPrev = tmppPrev;

			return findNode;
		}

		this->Next();
	}

	pCurrent = tmppCurrent;
	pNext = tmppNext;
	pPrev = tmppPrev;

	return NULL;
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopBegin(TKey _key, TData* _data)
{
	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data, pFirst);

	if (pCurrent == pFirst)
		pPrev = newNode;

	pFirst = newNode;
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopEnd(TKey _key, TData* _data)
{
	TNode<TKey, TData>* tmppCurrent = pCurrent;
	TNode<TKey, TData>* tmppNext = pNext;
	TNode<TKey, TData>* tmppPrev = pPrev;

	this->Reset();

	while (pNext)
		this->Next();

	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data);

	if (!pFirst)
		pFirst = newNode;
	else
		pCurrent->pNext = newNode;

	if (tmppCurrent == pCurrent)
		pNext = newNode;
	else
		pNext = tmppNext;

	pCurrent = tmppCurrent;
	pPrev = tmppPrev;
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopBefore(TKey _superKey, TKey _key, TData* _data)
{
	TNode<TKey, TData>* tmppCurrent = pCurrent;
	TNode<TKey, TData>* tmppNext = pNext;
	TNode<TKey, TData>* tmppPrev = pPrev;

	this->Reset();

	if ((this->IsEnded()) || (pFirst->key == _superKey))
	{
		this->PopBegin(_key, _data);
		pCurrent = pFirst;
		return;
	}

	TNode<TKey, TData>* nodeFind = Search(_superKey);

	if (!nodeFind)
	{
		throw Exception("Error: key didn't find!");
		return;
	}

	while (pCurrent != nodeFind)
		this->Next();

	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data, pCurrent);
	pPrev->pNext = newNode;

	if (tmppCurrent == pPrev)
		pNext = newNode;
	else
		pNext = tmppNext;

	if (tmppCurrent == pCurrent)
		pPrev = newNode;
	else
		pPrev = tmppPrev;

	pCurrent = tmppCurrent;
};

template<typename TKey, class TData>
void TList<TKey, TData>::PopAfter(TKey _superKey, TKey _key, TData* _data)
{
	TNode<TKey, TData>* tmppCurrent = pCurrent;
	TNode<TKey, TData>* tmppNext = pNext;
	TNode<TKey, TData>* tmppPrev = pPrev;

	this->Reset();

	TNode<TKey, TData>* nodeFind = Search(_superKey);

	if (!nodeFind)
	{
		throw Exception("Error: key didn't find!");
		return;
	}

	while (pCurrent != nodeFind)
		this->Next();

	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_key, _data, pNext);
	pCurrent->pNext = newNode;

	if (tmppCurrent == pCurrent)
		pNext = newNode;
	else
		pNext = tmppNext;

	if (tmppCurrent == pNext)
		pPrev = newNode;
	else
		pPrev = tmppPrev;

	pCurrent = tmppCurrent;
};

template<typename TKey, class TData>
void TList<TKey, TData>::Delete(TKey _key)
{
	if (!pFirst)
		throw Exception("Error: list is empty!");

	if (pFirst->key == _key)
	{
		if (pCurrent == pFirst)
		{
			pCurrent = pNext;
			if (pNext)
				pNext = pNext->pNext;
			else
				pNext = NULL;

			delete pFirst;
			pFirst = pCurrent;

			return;
		}

		if (pCurrent == pFirst->pNext)
		{
			pPrev = NULL;

			delete pFirst;
			pFirst = pCurrent;

			return;
		}

		delete pFirst;

		return;
	}

	TNode<TKey, TData>* tmppCurrent = pCurrent;
	TNode<TKey, TData>* tmppPrev = pPrev;
	TNode<TKey, TData>* tmppNext = pNext;

	this->Reset();

	TNode<TKey, TData>* nodeFind = Search(_key);

	if (!nodeFind)
	{
		throw Exception("Error: key didn't find!");
		return;
	}

	while (pCurrent != nodeFind)
		this->Next();

	pPrev->pNext = pNext;

	if (tmppCurrent == pCurrent)
	{
		pCurrent = tmppNext;
		pNext = pCurrent->pNext;
		delete nodeFind;

		return;
	}

	if (tmppCurrent == pPrev)
	{
		pCurrent = pPrev;
		pPrev = tmppPrev;
		pNext = pCurrent->pNext;
		delete nodeFind;

		return;
	}

	if (tmppCurrent == pNext)
	{
		pCurrent = pNext;
		pNext = pCurrent->pNext;
		delete nodeFind;

		return;
	}

	pNext = tmppCurrent->pNext;
	pCurrent = tmppCurrent;
	delete nodeFind;

	return;
};

template<typename TKey, class TData>
ostream& operator<<(ostream& _out, TList<TKey, TData>& _list)
{
	if (!_list.pFirst)
	{
		_out << "List is empty!" << endl;
		return _out;;
	}

	TNode<TKey, TData>* tmppCurrent = _list.pCurrent;
	TNode<TKey, TData>* tmppNext = _list.pNext;
	TNode<TKey, TData>* tmppPrev = _list.pPrev;

	_list.Reset();

	while (!_list.IsEnded())
	{
		_out << _list.pCurrent->key << " ";
		_list.Next();
	}

	_out << endl;

	_list.pCurrent = tmppCurrent;
	_list.pNext = tmppNext;
	_list.pPrev = tmppPrev;

	return _out;
};

#endif