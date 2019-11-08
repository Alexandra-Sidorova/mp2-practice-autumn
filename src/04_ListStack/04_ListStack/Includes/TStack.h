#ifndef _TSTACK_H_
#define _TSTACK_H_

enum typeStack {arrayStack, listStack};

template<typename ValType>
class TStack
{
public:
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;

	virtual void Push(ValType) = 0;
	virtual void Pop() = 0;
	virtual ValType TopWatch() const = 0;
};

#endif 