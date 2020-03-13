#include "Dijkstra.h"
#include "DHeap.h"
#include "Edge.h"
#include "SeparatedSet.h"
#include "Mark.h"

#include <cmath>
#include <algorithm>

#define D 3

float* Dijkstra::Algorithm(Graph _graph, int _start, vector<vector<int> >& _paths)
{
	if (_start < 0 || _start >= _graph.GetCountVertices())
		throw Exception("Incorrect start vertex!");

	float* dist = new float[_graph.GetCountVertices()];
	int* vertices = new int[_graph.GetCountVertices()];
	Mark* marks = new Mark[_graph.GetCountVertices()];

	for (int i = 0; i < _graph.GetCountVertices(); i++)
	{
		dist[i] = std::numeric_limits<float>::infinity();
		marks[i].dist = std::numeric_limits<float>::infinity();
		vertices[i] = _start;
		marks[i].vert = i;
	}

	dist[_start] = 0;
	marks[_start].dist = 0;

	DHeap<Mark> markQueue(_graph.GetCountVertices(), _graph.GetCountVertices(), D, marks);
	float* adjMatrix = _graph.AdjacencyMatrix();

	while (markQueue.GetCurrentSize() != 0)
	{
		Mark mark = markQueue.WatchMin();		
		markQueue.PopMin();

		for (int i = 0; i < _graph.GetCountVertices(); i++)
		{
			if ((adjMatrix[i * _graph.GetCountVertices() + mark.vert] == 1) && 
				(dist[mark.vert] + adjMatrix[mark.vert * _graph.GetCountVertices() + i] < dist[i]))
			{
				dist[i] = dist[mark.vert] + adjMatrix[mark.vert * _graph.GetCountVertices() + i];
				marks[i].dist = dist[i];
				vertices[i] = mark.vert;
			}
		}

		markQueue.Heapify();
	}

	_paths.resize(_graph.GetCountVertices());

	for (int i = 0; i < _graph.GetCountVertices(); i++)
	{
		int v = vertices[i];
		int count = 1;
		_paths[i].resize(_graph.GetCountVertices() - 1);

		while (v != _start)
		{
			_paths[i][count - 1] = v;
			v = vertices[v];
			count++;
		}
		
		_paths[i][count - 1] = _start;
		_paths[i].resize(count);
		reverse(_paths[i].begin(), _paths[i].end());
	}

	return dist;
};