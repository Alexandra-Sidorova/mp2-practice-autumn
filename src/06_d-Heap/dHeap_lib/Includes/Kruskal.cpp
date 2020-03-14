#include "Kruskal.h"
#include "DHeap.h"
#include "Edge.h"
#include "SeparatedSet.h"

#include <cmath>
#include <algorithm>

#define D 3

using namespace std;

void Kruskal::Algorithm(const Graph& _graph, vector<vector<Edge> >&  _newGraph)
{
	SeparatedSet vertices(_graph.GetCountVertices());
	
	for(int i = 0; i < _graph.GetCountVertices(); i++)
		vertices.CreateSingleton(i);

	Edge* listOfEdges = new Edge[_graph.GetCountVertices() * (_graph.GetCountVertices() - 1) / 2];
	int countOfEdges = 0;

	_graph.ListOfEdges(listOfEdges, countOfEdges);
	if (countOfEdges == 0)
		return;

	DHeap<Edge> edgesHeap (countOfEdges, countOfEdges, D, listOfEdges);
	edgesHeap.Heapify();

	Edge* edgesNewGraph = new Edge[_graph.GetCountVertices() - 1];
	int countOfNewEdges = 0;

	while (edgesHeap.GetCurrentSize() != 0)
	{
		Edge edge = edgesHeap.WatchMin();
		int setStart = vertices.Definition(edge.GetStart());
		int setEnd = vertices.Definition(edge.GetEnd());

		if (setStart != setEnd)
		{
			vertices.Union(setStart, setEnd);
			edgesNewGraph[countOfNewEdges++] = edge;
		}

		edgesHeap.PopMin();
	}

	vector<int> nameOfConnect;

	for (int i = 0; i < countOfNewEdges; i++)
	{
		int j = 0;

		for (j = 0; j < i; j++)
			if (vertices.Definition(edgesNewGraph[i].GetStart()) == vertices.Definition(edgesNewGraph[j].GetStart()))
				break;

		if (j == i)
			nameOfConnect.push_back(vertices.Definition(edgesNewGraph[i].GetStart()));
	}
	
	_newGraph.resize(nameOfConnect.size());

	for (int i = 0; i < countOfNewEdges; i++)
	{
		for (int j = 0; j < nameOfConnect.size(); j++)
		{
			if (vertices.Definition(edgesNewGraph[i].GetStart()) == nameOfConnect[j])
				_newGraph[j].push_back(edgesNewGraph[i]);
		}
	}

	delete[] listOfEdges;
	delete[] edgesNewGraph;
};