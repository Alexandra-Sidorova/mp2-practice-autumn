#include "Graph.h"

using namespace std;

Graph::Graph(int _size)
{
	if (_size <= 0)
		throw Exception("Incorrect size of graph!");

	countVertices = _size;
	weights = new float[countVertices * countVertices];

	for (int i = 0; i < countVertices; i++)
		for (int j = 0; j < i; j++)
		{
			weights[i * countVertices + j] = -1;
			weights[j * countVertices + i] = -1;
		}
};

Graph::Graph(float* _vector, int _size)
{
	if (_size <= 0)
		throw Exception("Incorrect size of graph!");

	if (_vector == nullptr)
		throw Exception("Vector is empty!");

	countVertices = _size;
	weights = new float[countVertices * countVertices];

	for (int i = 0; i < countVertices; i++)
		for (int j = 0; j <= i; j++)
		{
			weights[i * countVertices + j] = _vector[i * countVertices + j];
			weights[j * countVertices + i] = weights[i * countVertices + j];
		}
};

Graph::Graph(const Graph& _graph)
{
	countVertices = _graph.countVertices;
	weights = new float[countVertices * countVertices];

	for (int i = 0; i < countVertices; i++)
		for (int j = 0; j <= i; j++)
		{
			weights[i * countVertices + j] = _graph.weights[i * countVertices + j];
			weights[j * countVertices + i] = weights[i * countVertices + j];
		}
};

Graph::~Graph()
{
	countVertices = 0;
	delete[] weights;
};
//-------------------------------------------------------

int Graph::GetCountVertices() const
{
	return countVertices;
};

void Graph::Random()
{
	for (int i = 0; i < countVertices; i++)
	{
		for (int j = 0; j < i; j++)
		{
			weights[i * countVertices + j] = (int)(rand() % 20) - 1;
			weights[j * countVertices + i] = weights[i * countVertices + j];
		}

		weights[i * countVertices + i] = -1;
	}
};

void Graph::ListOfEdges(Edge* _edges, int& countEdges) const
{
	if (_edges == nullptr)
		_edges = new Edge[countVertices * (countVertices - 1) / 2];
	
	countEdges = 0;

	for (int i = 0; i < countVertices; i++)
		for (int j = 0; j < i; j++)
		{
			if (weights[i * countVertices + j] >= 0)
			{
				Edge edge(weights[i * countVertices + j], i, j);
				_edges[countEdges++] = edge;
			}
		}
};

float* Graph::AdjacencyMatrix() const
{
	float* matrix = new float[countVertices * countVertices];

	for (int i = 0; i < countVertices; i++)
		for (int j = 0; j <= i; j++)
		{
			if (weights[i * countVertices + j] >= 0)
			{
				matrix[i * countVertices + j] = weights[i * countVertices + j];
				matrix[j * countVertices + i] = weights[j * countVertices + i];
			}
			else
			{
				matrix[i * countVertices + j] = 0;
				matrix[j * countVertices + i] = 0;
			}
		}

	return matrix;
};

ostream& operator<<(ostream& _out, const Graph& _graph)
{
	for (int i = 0; i < _graph.countVertices; i++)
	{
		for (int j = 0; j < i; j++)
			_out << "\t";
		for (int j = i; j < _graph.countVertices; j++)
			_out << _graph.weights[j * _graph.countVertices + i] << "\t";
		_out << endl;
	}

	return _out;
};