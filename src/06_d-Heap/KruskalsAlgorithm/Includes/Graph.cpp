#include "Graph.h"

using namespace std;

Graph::Graph(int _size)
{
	countVertices = _size;
	vector<vector<float> > weights(countVertices);

	for (int i = 0; i < countVertices; i++)
		weights[i].resize(i + 1);
};

Graph::Graph(vector<vector<float> > _graph)
{
	countVertices = _graph.size();
	vector<vector<float> > weights(countVertices);

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
	vector<vector<float> > weights(countVertices);

	for (int i = 0; i < countVertices; i++)
		weights[i].resize(i + 1);

	for (int i = 0; i <= _edges.GetCurrentSize(); i++)
		weights[_edges.GetElems()[i].GetStart()][_edges.GetElems()[i].GetEnd()] = _edges.GetElems()[i].GetWeight();
};

Graph::Graph(const Graph& _graph)
{
	countVertices = _graph.countVertices;
	vector<vector<float> > weights(countVertices);

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
		for (int j = 0; j <= i; j++)
			_out << _graph.weights[i][j] << "\t";
		_out << endl;
	}

	return _out;
};