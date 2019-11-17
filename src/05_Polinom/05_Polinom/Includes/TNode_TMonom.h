#ifndef _TNODE_TMONOM_H_
#define _TNODE_TMONOM_H_

#include "exceptions.h"
#include "TNode.h"

template<>
class TNode <int, float>
{
public:
	int key;  // degree, 3 symbols (xyz)
	float pData;  // coeff
	TNode<int, float>* pNext;

	TNode() : key(0), pData(0), pNext(NULL) {}
	TNode(int _key, float _data, TNode* _node = NULL) : key(_key), pData(_data), pNext(_node) {}
	TNode(const TNode& _copy) : key(_copy.key), pData(_copy.pData), pNext(_copy.pNext) {}
	~TNode()
	{
		key = 0;
		pData = 0;
		pNext = NULL;
	}
};

#endif
