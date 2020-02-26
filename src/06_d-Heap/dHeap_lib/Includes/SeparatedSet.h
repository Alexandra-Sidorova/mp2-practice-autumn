#ifndef _SEPARATEDSET_H_
#define _SEPARATEDSET_H_

class SeparatedSet
{
private:
	int size;
	int* arr;

public:
	SeparatedSet(int, int*);
	~SeparatedSet();

	void CreateSingleton();
	void Union(int, int);
	int Definition(int);
};

#endif
