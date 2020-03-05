#include "Graph.h"

using namespace std;

Graph::Graph(int _size)
{
	countVertices = _size;
	weights.resize(countVertices);

	for (int i = 0; i < countVertices; i++)
	{
		weights[i].resize(i + 1);

		for (int j = 0; j <= i; j++)
			weights[i][j] = -1;
	}
};

Graph::Graph(vector<vector<float> > _graph)
{
	countVertices = _graph.size();
	weights.resize(countVertices);

	for (int i = 0; i < countVertices; i++)
	{
		weights[i].resize(i + 1);

		for (int j = 0; j <= i; j++)
			weights[i][j] = _graph[i][j];

	}
};

Graph::Graph(DHeap<Edge> _edges, int _size)
{
	countVertices = _size;
	weights.resize(countVertices);

	for (int i = 0; i < countVertices; i++)
	{
		weights[i].resize(i + 1);

		for (int j = 0; j <= i; j++)
			weights[i][j] = -1;
	}

	for (int i = 0; i < _edges.GetCurrentSize(); i++)
		weights[_edges.GetElems()[i].GetStart()][_edges.GetElems()[i].GetEnd()] = _edges.GetElems()[i].GetWeight();
};

Graph::Graph(const Graph& _graph)
{
	countVertices = _graph.countVertices;
	weights.resize(countVertices);

	for (int i = 0; i < countVertices; i++)
	{
		weights[i].resize(i + 1);

		for (int j = 0; j <= i; j++)
			weights[i][j] = _graph.weights[i][j];
	}
};

Graph::~Graph()
{
	for (int i = 0; i < countVertices; i++)
		weights[i].clear();

	weights.clear();
	countVertices = 0;
};
//-------------------------------------------------------

int Graph::GetCountVertices() const
{
	return countVertices;
};

DHeap<Edge> Graph::CreateEdges()
{
	DHeap<Edge> edges(countVertices * countVertices, 1);

	for (int i = 0; i < countVertices; i++)
		for (int j = 0; j < i; j++)
		{
			if (weights[i][j] >= 0)
			{
				Edge edge(weights[i][j], i, j);
				edges.Push(edge);
			}
		}

	edges.Heapify();
	return edges;
};

void Graph::Random()
{
	for (int i = 0; i < countVertices; i++)
	{
		for (int j = 0; j < i; j++)
			weights[i][j] = (int)(rand() % 20) - 1;
	}
};

int* Graph::Neighborhood(int _v)
{
	int* vertices = new int[countVertices - 1];
	int count = 0;

	for (int i = 0; i < _v; i++)
		if (weights[_v][i] != -1)
			vertices[count++] = i;

	for(int i = _v + 1; i < countVertices; i++)
		if(weights[i][_v] != -1)
			vertices[count++] = i;

	return vertices;
};

int Graph::DegreeVert(int _v) const
{
	int count = 0;

	for (int i = 0; i < _v; i++)
		if (weights[_v][i] != -1)
			count++;

	for (int i = _v + 1; i < countVertices; i++)
		if (weights[i][_v] != -1)
			count++;

	return count;
};

float Graph::Weight(int _i, int _j) const
{
	return weights[max(_i, _j)][min(_i,_j)];
}

istream& operator>>(istream& _in, Graph& _graph)
{
	for (int i = 0; i < _graph.countVertices; i++)
		for (int j = 0; j <= i; j++)
			_in >> _graph.weights[i][j];

	return _in;
};

ostream& operator<<(ostream& _out, const Graph& _graph)
{
	for (int i = 0; i < _graph.countVertices; i++)
	{
		for (int j = 0; j < i; j++)
			_out << "\t";
		for (int j = i; j < _graph.countVertices; j++)
			_out << _graph.weights[j][i] << "\t";
		_out << endl;
	}

	return _out;
};