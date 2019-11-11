#ifndef _TSTACK_H_
#define _TSTACK_H_


#define SIZE_STACK 64

enum typeStack {arrayStack, listStack};

template<typename ValType> class TArrayStack;
template<typename ValType> class TListStack;

template<typename ValType>
class TStack
{
public:
	static TStack* Create(typeStack);

	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;

	virtual void Push(ValType) = 0;
	virtual void Pop() = 0;
	virtual ValType TopWatch() const = 0;
};

template<typename ValType>
TStack<ValType>* TStack<ValType>::Create(typeStack type)
{
	if (type == arrayStack)
	{
		return new TArrayStack<ValType>(SIZE_STACK);
	}
	if (type == listStack)
	{
		return new TListStack<ValType>();
	}
	throw "Not implemented";
};

#endif 