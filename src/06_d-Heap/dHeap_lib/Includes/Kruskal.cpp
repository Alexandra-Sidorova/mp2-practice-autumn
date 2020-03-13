#include "Kruskal.h"
#include "DHeap.h"
#include "Edge.h"
#include "SeparatedSet.h"

#include <cmath>
#include <algorithm>

#define D 3

using namespace std;

Edge* Kruskal::Algorithm(const Graph& _graph)
{
	SeparatedSet vertices(_graph.GetCountVertices());
	
	for(int i = 0; i < _graph.GetCountVertices(); i++)
		vertices.CreateSingleton(i);

	Edge* listOfEdges;
	int countOfEdges = 0;

	_graph.ListOfEdges(listOfEdges, countOfEdges);
	DHeap<Edge> edgesHeap (countOfEdges, countOfEdges, D, listOfEdges);
	edgesHeap.Heapify();

	Edge* frameGraph = new Edge[_graph.GetCountVertices() - 1];
	int countOfEdges = 0;

	while ((countOfEdges != (_graph.GetCountVertices() - 1)) && (edgesHeap.GetCurrentSize() != 0))
	{
		Edge edge = edgesHeap.WatchMin();
		int setStart = vertices.Definition(edge.GetStart());
		int setEnd = vertices.Definition(edge.GetEnd());

		if (setStart != setEnd)
		{
			vertices.Union(setStart, setEnd);
			frameGraph[countOfEdges++] = edge;
		}

		edgesHeap.PopMin();
	}

	return frameGraph;
};