#ifndef _SEPARATEDSET_H_
#define _SEPARATEDSET_H_

class SeparatedSet
{
private:
	int size;
	int* arr;

public:
	SeparatedSet(int);
	SeparatedSet(int, int*);
	SeparatedSet(const SeparatedSet&);
	~SeparatedSet();

	void CreateSingleton(int);
	void Union(int, int);
	int Definition(int) const;
};

#endif
