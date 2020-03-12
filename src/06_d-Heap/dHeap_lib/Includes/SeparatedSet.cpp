#include "SeparatedSet.h"
#include "exceptions.h"

SeparatedSet::SeparatedSet(int _size)
{
	if (_size <= 0)
		throw Exception("Incorrect data!");
	size = _size;

	arr = new int[size];
	for (int i = 0; i < size; i++)
		arr[i] = -1;
};

SeparatedSet::SeparatedSet(int _size, int* _arr)
{
	if (_size <= 0 || _arr == NULL)
		throw Exception("Incorrect data!");
	size = _size;

	arr = new int[size];
	for (int i = 0; i < size; i++)
		arr[i] = _arr[i];
};

SeparatedSet::SeparatedSet(const SeparatedSet& _copy)
{
	size = _copy.size;
	arr = new int[size];
	for (int i = 0; i < size; i++)
		arr[i] = _copy.arr[i];
};

SeparatedSet::~SeparatedSet()
{
	size = 0;
	delete[] arr;
};
//----------------------------------------------------------

void SeparatedSet::CreateSingleton(int i)
{
	arr[i] = i;
};

void SeparatedSet::Union(int i, int j)
{
	if (i < 0 || j < 0 || i >= size || j >= size)
		throw Exception("[Error] Incorrect set names!");

	for (int k = 0; k < size; k++)
		if (arr[k] == i)
			arr[k] = j;
};

int SeparatedSet::Definition(int i) const
{
	if (i < 0 || i >= size)
		throw Exception("[Error] Incorrect set number!");

	return arr[i];
};