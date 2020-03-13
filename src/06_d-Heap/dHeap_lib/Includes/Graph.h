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
	float* weights;

public:
	Graph(int);
	Graph(float*, int);
	Graph(const Graph&);
	~Graph();

	int GetCountVertices() const;

	void Random();
	void ListOfEdges(Edge*, int&) const;
	float* AdjacencyMatrix() const;

	friend ostream& operator<<(ostream&, const Graph&);
};

#endif