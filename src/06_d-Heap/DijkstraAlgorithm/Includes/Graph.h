#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <iostream>

#include "DHeap.h"
#include "Edge.h"

class Graph
{
private:
	int countVertices;
	vector<vector<float> > weights;

public:
	Graph(int);
	Graph(vector<vector<float> >);
	Graph(DHeap<Edge>, int);
	Graph(const Graph&);
	~Graph();

	int GetCountVertices() const;

	DHeap<Edge> CreateEdges();
	void Random();
	int* Neighborhood(int);
	int DegreeVert(int);
	float Weight(int, int);

	friend istream& operator>>(istream&, Graph&);
	friend ostream& operator<<(ostream&, const Graph&);
};

#endif