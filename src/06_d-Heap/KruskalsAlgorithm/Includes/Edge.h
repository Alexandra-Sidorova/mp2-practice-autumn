#ifndef _EDGE_H_
#define _EDGE_H_

class Edge
{
private:
	int weight;
	int start;
	int end;

public:
	Edge();
	Edge(int, int, int);
	~Edge();

	int GetWeight() const;
	int GetStart() const;
	int GetEnd() const;

	bool operator>(const Edge) const;
	bool operator>=(const Edge) const;
	bool operator<(const Edge) const;
	bool operator<=(const Edge) const;


};

#endif