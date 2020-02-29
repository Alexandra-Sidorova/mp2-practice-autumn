#include "Kruskal.h"
#include "DHeap.h"
#include "Edge.h"
#include "SeparatedSet.h"

#include <cmath>
#include <algorithm>

using namespace std;

Graph Kruskal::Algorithm(Graph _graph)
{
	SeparatedSet vertices(_graph.GetCountVertices());
	vertices.CreateSingleton();

	DHeap<Edge> edges = _graph.CreateEdges();
	DHeap<Edge> currentNewGraph(_graph.GetCountVertices(), 1);

	while ((currentNewGraph.GetCurrentSize() != (_graph.GetCountVertices() - 1)) && (edges.GetCurrentSize() != 0))
	{
		Edge edge = edges.WatchMin();
		int setStart = vertices.Definition(edge.GetStart());
		int setEnd = vertices.Definition(edge.GetEnd());

		if (setStart != setEnd)
		{
			vertices.Union(setStart, setEnd);
			currentNewGraph.Push(edge);
		}

		edges.PopMin();
	}

	return Graph(currentNewGraph, _graph.GetCountVertices());
};