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
	Graph();
	Graph(int);
	Graph(float*, int);
	Graph(const Graph&);
	~Graph();

	int GetCountVertices() const;

	void GenerateCommonGraph();
	void GenerateConnectGraph();
	void SpecialRandom();
	void ListOfEdges(Edge*, int&) const;
	float* AdjacencyMatrix() const;
	bool IsConnected() const;

	friend istream& operator>>(istream&, Graph&);
	friend ostream& operator<<(ostream&, const Graph&);
};

#endif