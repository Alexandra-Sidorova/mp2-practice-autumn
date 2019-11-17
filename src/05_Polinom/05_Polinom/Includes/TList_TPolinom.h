#ifndef _TLIST_TPOLINOM_H_
#define _TLIST_TPOLINOM_H_

#include <iostream>

#include "TNode_TMonom.h"
#include "TList.h"
#include "exceptions.h"

template<>
class TList <int, float>
{
private:
	TNode<int, float>* pFirst;
	TNode<int, float>* pCurrent;
	TNode<int, float>* pNext;
	TNode<int, float>* pPrev;

public:
	TList();
	TList(const TList&);
	TList(const TNode<int, float>*);
	~TList();

	void Reset();
	void Next();
	bool IsEnded() const;
	TNode<int, float>* GetpFirst() const;
	TNode<int, float>* GetpCurrent() const;

	void SortData();
	TNode<int, float>* Search(int);
	void PushBegin(int, float);
	void PushEnd(int, float);
	void PushBefore(int, int, float);
	void PushAfter(int, int, float);
	void Delete(int);

	friend ostream& operator<<(ostream& _out, TList<int, float>& _list)
	{
		if (!_list.pFirst)
		{
			_out << "List is empty!" << endl;
			return _out;;
		}

		TNode<int, float>* tmppCurrent = _list.pCurrent;
		TNode<int, float>* tmppNext = _list.pNext;
		TNode<int, float>* tmppPrev = _list.pPrev;

		_list.Reset();

		while (!_list.IsEnded())
		{
			_out << _list.pCurrent->pData << " ";
			_list.Next();
		}

		_out << endl;

		_list.pCurrent = tmppCurrent;
		_list.pNext = tmppNext;
		_list.pPrev = tmppPrev;

		return _out;
	};
};
//-----------------------------------------------------------------

TList<int, float>::TList()
{
	pFirst = pNext = pPrev = pCurrent = NULL;
};

TList<int, float>::TList(const TList& _copy)
{
	pNext = pPrev = pCurrent = NULL;

	if (!_copy.pFirst)
		pFirst = NULL;
	else
	{
		pFirst = new TNode<int, float>(*_copy.pFirst);
		pFirst->pNext = NULL;
		pCurrent = pFirst;

		TNode<int, float>* iter = new TNode<int, float>;
		iter = _copy.pFirst;

		while (iter->pNext)
		{
			iter = iter->pNext;
			pCurrent->pNext = new TNode<int, float>(*iter);

			pPrev = pCurrent;
			pCurrent = pCurrent->pNext;
			pNext = pCurrent->pNext = NULL;
		}

		pPrev = NULL;
		pCurrent = pFirst;
		pNext = pFirst->pNext;
	}
};

TList<int, float>::TList(const TNode<int, float>* _node)
{
	pNext = pPrev = pCurrent = NULL;

	if (!_node)
		pFirst = NULL;
	else
	{
		TNode<int, float>* node = new TNode<int, float>(*_node);
		pFirst = node;

		TNode<int, float>* iter = _node->pNext;
		TNode<int, float>* prev = pFirst;

		while (iter)
		{
			TNode<int, float>* tmp = new TNode<int, float>(*iter);
			prev->pNext = tmp;
			prev = tmp;
			iter = iter->pNext;
		}

		pCurrent = pFirst;
		pNext = pCurrent->pNext;
	}
};

TList<int, float>::~TList()
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

void TList<int, float>::Reset()
{
	pPrev = NULL;
	pCurrent = pFirst;
	if (pFirst)
		pNext = pCurrent->pNext;
	else
		pNext = NULL;
};

void TList<int, float>::Next()
{
	pPrev = pCurrent;
	pCurrent = pNext;

	if (pCurrent)
		pNext = pCurrent->pNext;
	else
		pNext = NULL;
};

bool TList<int, float>::IsEnded() const
{
	return (pCurrent == NULL);
};

TNode<int, float>* TList<int, float>::GetpFirst() const
{
	return pFirst;
};

TNode<int, float>* TList<int, float>::GetpCurrent() const
{
	return pCurrent;
};
//-----------------------------------------------------------------

void TList<int, float>::SortData()
{
	TNode<int, float>* last = new TNode<int, float>;
	TNode<int, float>* tmpfirst = new TNode<int, float>;
	bool first = true;

	while (this->pFirst)
	{
		TNode<int, float>* min = new TNode<int, float>;
		min = pFirst;

		while (!this->IsEnded())
		{
			if (pCurrent->pData < min->pData)
				min = pCurrent;
			this->Next();
		}

		this->Reset();
		while ((this->pCurrent != min) && (!this->IsEnded()))
			this->Next();

		if (pCurrent == pFirst)
			pFirst = pCurrent = pNext;
		else if (pNext == NULL)
			pPrev->pNext = NULL;
		else 
			pPrev->pNext = pNext;
		this->Reset();

		if (first)
		{
			tmpfirst = min;
			first = false;
		}
		else last->pNext = min;
		last = min;
	}

	last->pNext = NULL;
	pFirst = tmpfirst;
	pPrev = NULL;
	pCurrent = pFirst;
	pNext = pCurrent->pNext;
};

TNode<int, float>* TList<int, float>::Search(int _key)
{
	TNode<int, float>* tmppCurrent = pCurrent;
	TNode<int, float>* tmppNext = pNext;
	TNode<int, float>* tmppPrev = pPrev;

	this->Reset();

	while (!this->IsEnded())
	{
		if (_key == pCurrent->key)
		{
			TNode<int, float>* findNode = pCurrent;
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

void TList<int, float>::PushBegin(int _key, float _data)
{
	TNode<int, float>* newNode = new TNode<int, float>(_key, _data, pFirst);

	if (pCurrent == pFirst)
		pPrev = newNode;

	pFirst = newNode;
};

void TList<int, float>::PushEnd(int _key, float _data)
{
	TNode<int, float>* tmppCurrent = pCurrent;
	TNode<int, float>* tmppNext = pNext;
	TNode<int, float>* tmppPrev = pPrev;

	this->Reset();

	while (pNext)
		this->Next();

	TNode<int, float>* newNode = new TNode<int, float>(_key, _data);

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

void TList<int, float>::PushBefore(int _superKey, int _key, float _data)
{
	TNode<int, float>* tmppCurrent = pCurrent;
	TNode<int, float>* tmppNext = pNext;
	TNode<int, float>* tmppPrev = pPrev;

	this->Reset();

	if ((this->IsEnded()) || (pFirst->key == _superKey))
	{
		this->PushBegin(_key, _data);
		pCurrent = pFirst;
		return;
	}

	TNode<int, float>* nodeFind = Search(_superKey);

	if (!nodeFind)
	{
		throw Exception("Error: key didn't find!");
		return;
	}

	while (pCurrent != nodeFind)
		this->Next();

	TNode<int, float>* newNode = new TNode<int, float>(_key, _data, pCurrent);
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

void TList<int, float>::PushAfter(int _superKey, int _key, float _data)
{
	TNode<int, float>* tmppCurrent = pCurrent;
	TNode<int, float>* tmppNext = pNext;
	TNode<int, float>* tmppPrev = pPrev;

	this->Reset();

	TNode<int, float>* nodeFind = Search(_superKey);

	if (!nodeFind)
	{
		throw Exception("Error: key didn't find!");
		return;
	}

	while (pCurrent != nodeFind)
		this->Next();

	TNode<int, float>* newNode = new TNode<int, float>(_key, _data, pNext);
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

void TList<int, float>::Delete(int _key)
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

	TNode<int, float>* tmppCurrent = pCurrent;
	TNode<int, float>* tmppPrev = pPrev;
	TNode<int, float>* tmppNext = pNext;

	this->Reset();

	TNode<int, float>* nodeFind = Search(_key);

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

#endif
