#include "Kruskal.h"
#include "DHeap.h"
#include "Edge.h"
#include "SeparatedSet.h"

#include <cmath>
#include <algorithm>

using namespace std;

DHeap<Edge> Kruskal::CreateEdges(vector<vector<float> > _graph)
{
	DHeap<Edge> edges(_graph.size() * _graph.size(), 1);

	for (int i = 0; i < _graph.size(); i++)
		for (int j = i; j < _graph[i].size(); j++)
		{
			if (_graph[i][j] >= 0)
			{
				Edge edge(_graph[i][j], i, j);
				edges.Push(edge);
			}
		}

	edges.Heapify();
	return edges;
};

vector<vector<float> > Kruskal::CreateGraph(DHeap<Edge> _edges, int _size)
{
	vector<vector<float> > graph(_size);
	DHeap<Edge> tmp(_edges);

	for (int i = 0; i < _size; i++)
		graph[i].resize(i);

	while (tmp.GetCurrentSize() != 0)
	{
		Edge edge = tmp.WatchMin();
		graph[max(edge.GetStart(), edge.GetEnd())][min(edge.GetStart(), edge.GetEnd())] = edge.GetWeight();
		tmp.PopMin();
	}

	return graph;
};

vector<vector<float> > Kruskal::Algorithm(vector<vector<float> > _graph)
{
	SeparatedSet vertices(_graph.size());
	vertices.CreateSingleton();

	DHeap<Edge> edges = CreateEdges(_graph);
	DHeap<Edge> currentNewGraph(edges.GetCurrentSize(), 1);

	while ((currentNewGraph.GetCurrentSize() != (_graph.size() - 1)) && (edges.GetCurrentSize() != 0))
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

	return CreateGraph(currentNewGraph, _graph.size());
};