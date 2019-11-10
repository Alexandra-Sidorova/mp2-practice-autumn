#ifndef _TARRAYSTACK_H_
#define _TARRAYSTACK_H

#include "exceptions.h"
#include "TStack.h"

using namespace std;

template<typename ValType>
class TArrayStack : public TStack<ValType>
{
private:
    int size;
    int top;
    ValType* elem;

public:
    TArrayStack(int);
    TArrayStack(const TArrayStack<ValType>&);
    ~TArrayStack();

    bool IsEmpty() const;
    bool IsFull() const;

    void Push(ValType);
    void Pop();
    ValType TopWatch() const;
};
//----------------------------------------------------

template<typename ValType>
TArrayStack<ValType>::TArrayStack(int _size) : size(_size)
{
    if (size <= 0)
        throw Exception("Not correct size of stack!");

    elem = new ValType[size];
    memset(elem, 0, sizeof(ValType) * size);

    top = 0;
};

template<typename ValType>
TArrayStack<ValType>::TArrayStack(const TArrayStack<ValType>& _copy) : size(_copy.size), top(_copy.top)
{
    elem = new ValType[size];
    memset(elem, _copy.elem, sizeof(ValType) * size);
};

template<typename ValType>
TArrayStack<ValType>::~TArrayStack()
{
    size = 0;
    top = 0;
    delete[] elem;
};
//----------------------------------------------------

template<typename ValType>
bool TArrayStack<ValType>::IsEmpty() const
{
    return(top == 0);
};

template<typename ValType>
bool TArrayStack<ValType>::IsFull() const
{
    return(top == size);
};
//----------------------------------------------------

template<typename ValType>
void TArrayStack<ValType>::Push(ValType _object)
{
    if (IsFull())
        throw Exception("Error: stack is full!");

    elem[top++] = _object;
};

template<typename ValType>
void TArrayStack<ValType>::Pop()
{
    if (IsEmpty())
        throw Exception("Error: stack is empty!");

    top--;
};

template<typename ValType>
ValType TArrayStack<ValType>::TopWatch() const
{
    if (IsEmpty())
        throw Exception("Error: stack is empty!");

    return (elem[top - 1]);
};

#endif