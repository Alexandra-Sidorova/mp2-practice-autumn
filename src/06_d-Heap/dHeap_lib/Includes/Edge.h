#ifndef _EDGE_H_
#define _EDGE_H_

#include <iostream>

using namespace std;

class Edge
{
private:
	float weight;
	int start;
	int end;

public:
	Edge();
	Edge(float, int, int);
	~Edge();

	int GetWeight() const;
	int GetStart() const;
	int GetEnd() const;

	const Edge& operator=(const Edge&);
	bool operator>(const Edge&) const;
	bool operator>=(const Edge&) const;
	bool operator<(const Edge&) const;
	bool operator<=(const Edge&) const;

	friend ostream& operator<<(ostream&, const Edge&);
};

#endif