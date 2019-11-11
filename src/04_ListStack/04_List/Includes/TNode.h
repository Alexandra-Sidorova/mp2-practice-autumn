#ifndef _TNODE_H_
#define _TNODE_H_

template<typename TKey, class TData>
class TNode
{
public:
	TKey key;
	TData* pData;
	TNode<TKey, TData>* pNext;

	TNode();
	TNode(TKey _key, TData* _data, TNode* _node = NULL);
	TNode(const TNode&);
	~TNode();
};
//----------------------------------------------

template<typename TKey, class TData>
TNode<TKey, TData>::TNode()
{
	key = 0;
	pData = NULL;
	pNext = NULL;
};

template<typename TKey, class TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _data, TNode<TKey, TData>* _node)
{
	key = _key;
	pData = _data;
	pNext = _node;
};

template<typename TKey, class TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& _copy)
{
	key = _copy.key;
	pData = _copy.pData;
	pNext = _copy.pNext;
};

template<typename TKey, class TData>
TNode<TKey, TData>::~TNode()
{
	key = 0;
	pData = NULL;
	pNext = NULL;
};

#endif
