#include "Dijkstra.h"
#include "DHeap.h"
#include "Edge.h"
#include "SeparatedSet.h"
#include "Mark.h"

#include <cmath>
#include <algorithm>

#define D 3

void Dijkstra::Algorithm(const Graph& _graph, const int _start, vector<vector<int> >& _paths, float* _result)
{
	if (_start < 0 || _start >= _graph.GetCountVertices())
		throw Exception("Incorrect start vertex!");

	if (!_graph.IsConnected())
		throw Exception("Graph must be connect connected!");

	int* vertices = new int[_graph.GetCountVertices()];
	Mark* marks = new Mark[_graph.GetCountVertices()];

	for (int i = 0; i < _graph.GetCountVertices(); i++)
	{
		marks[i].dist = std::numeric_limits<float>::infinity();
		vertices[i] = _start;
		marks[i].vert = i;
	}

	marks[_start].dist = 0;

	DHeap<Mark> markQueue(_graph.GetCountVertices(), _graph.GetCountVertices(), D, marks);
	markQueue.Heapify();

	float* adjMatrix = _graph.AdjacencyMatrix();

	while (markQueue.GetCurrentSize() != 0)
	{
		Mark mark = markQueue.WatchMin();		
		markQueue.PopMin();

		for (int i = 0; i < _graph.GetCountVertices(); i++)
		{
			int idx = marks[i].vert * _graph.GetCountVertices() + mark.vert;
			
			if ((adjMatrix[idx] >= 0) && (mark.dist + adjMatrix[idx] < marks[i].dist))
			{
				marks[i].dist = mark.dist + adjMatrix[idx];
				vertices[marks[i].vert] = mark.vert;
				adjMatrix[idx] = -1;
			}
		}

		markQueue.Heapify();
	}

	for (int i = 0; i < _graph.GetCountVertices(); i++)
		_result[marks[i].vert] = marks[i].dist;

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

	delete[] vertices;
	delete[] marks;
};