#include "Graph.h"

Graph::Graph()
{
	countVertices = 0;
	weights = nullptr;
};

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

void Graph::GenerateCommonGraph()
{
	for (int i = 0; i < countVertices; i++)
	{
		for (int j = 0; j < i; j++)
		{
			weights[i * countVertices + j] = (int)(rand() % 12) - 1;
			weights[j * countVertices + i] = weights[i * countVertices + j];
		}

		weights[i * countVertices + i] = -1;
	}
};

void Graph::GenerateConnectGraph()
{
	for (int i = 0; i < countVertices; i++)
	{
		for (int j = 0; j < i; j++)
		{
			weights[i * countVertices + j] = (int)(rand() % 12);
			weights[j * countVertices + i] = weights[i * countVertices + j];
		}

		weights[i * countVertices + i] = -1;
	}
};

void Graph::ListOfEdges(Edge* _edges, int& countEdges) const
{
	countEdges = 0;

	for (int i = 0; i < countVertices; i++)
		for (int j = 0; j < i; j++)
		{
			if (this->weights[i * countVertices + j] >= 0)
			{
				Edge edge(this->weights[i * countVertices + j], i, j);
				_edges[countEdges++] = edge;
			}
		}
};

float* Graph::AdjacencyMatrix() const
{
	return weights;
};

using namespace std;
istream& operator>>(istream& _in, Graph& _graph)
{
	int countOfEdges = 0;

	cout << "Enter the count of vertices: ";
	_in >> _graph.countVertices;
	if (_graph.countVertices <= 0)
		throw Exception("Count of vertices must be positive!");

	_graph.weights = new float[_graph.countVertices * _graph.countVertices];

	for (int i = 0; i < _graph.countVertices; i++)
		for (int j = 0; j < _graph.countVertices; j++)
			_graph.weights[i * _graph.countVertices + j] = -1;

	cout << "Enter the count of edges: ";
	_in >> countOfEdges;

	if ((countOfEdges > (_graph.countVertices * (_graph.countVertices - 1) / 2)) || (countOfEdges < 0))
		throw Exception("Count of Edges must be in [0, (countVertices * (countVertices - 1) / 2)]");

	for (int i = 0; i < countOfEdges; i++)
	{
		int v1, v2;

		cout << endl << "Enter the first vertex: ";
		_in >> v1;
		if ((v1 < 0) || (v1 >= _graph.countVertices))
			throw Exception("Not correct name ov vertex!");

		cout << "Enter the secound vertex: ";
		_in >> v2;
		if ((v2 < 0) || (v2 >= _graph.countVertices))
			throw Exception("Not correct name of vertex!");

		if (v1 == v2)
			throw Exception("First vertex is the secound!");

		if (_graph.weights[v1 * _graph.countVertices + v2] > 0)
			throw Exception("The edge between these vertices exists!");

		cout << "Enter the weight for edge: ";
		_in >> _graph.weights[v1 * _graph.countVertices + v2];
		if (_graph.weights[v1 * _graph.countVertices + v2] < 0)
			throw Exception("The edge between these vertices must be not negative!");
		_graph.weights[v2 * _graph.countVertices + v1] = _graph.weights[v1 * _graph.countVertices + v2];
	}

	cout << endl << "Graph is complete." << endl;

	return _in;
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