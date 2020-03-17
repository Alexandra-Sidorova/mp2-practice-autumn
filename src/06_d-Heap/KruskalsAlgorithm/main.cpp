#include <iostream>
#include <vector>
#include <time.h>

#include "exceptions.h"
#include "Kruskal.h"
#include "Graph.h"

#define RANDOM 15

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	cout << "##### TEST KRUSKAL'S ALGORITHMS #####" << endl;

	try
	{
		cout << endl << "CLASS EXAMPLE" << endl;
		
		float weights[36] = { -1, 8, -1, -1, 3, 2,
							  8, -1, 10, 1, 0, 2,
							 -1, 10, -1, 5, 2, 9,
							 -1, 1, 5, -1, 4, -1,
							  3, 0, 2, 4, -1, -1,
							  2, 2, 9, -1, -1, -1 };

		Graph graph(weights, 6);
		cout << graph;
		
		vector<vector<Edge> > newGraph;
		cout << "Kruskal's Algorithm is loading..." << endl;
		Kruskal::Algorithm(graph, newGraph);

		if (newGraph.size() == 0)
		{
			cout << "Graph don't have edges." << endl;
			return;
		}

		for (int i = 0; i < newGraph.size(); i++)
		{
			cout << endl << "Connection " << i << ": " << endl;

			for (int j = 0; j < newGraph[i].size(); j++)
				cout << newGraph[i][j] << endl;
		}

		newGraph.clear();
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << "RANDOM GRAPH" << endl;

		int size = 5;
		Graph graph(size);
		graph.GenerateCommonGraph();
		cout << graph;
		
		vector<vector<Edge> > newGraph;
		cout << "Kruskal's Algorithm is loading..." << endl;
		Kruskal::Algorithm(graph, newGraph);

		if (newGraph.size() == 0)
		{
			cout << "Graph don't have edges." << endl;
			return;
		}

		for (int i = 0; i < newGraph.size(); i++)
		{
			cout << endl << "Connection " << i << ": " << endl;

			for (int j = 0; j < newGraph[i].size(); j++)
				cout << newGraph[i][j] << endl;
		}

		newGraph.clear();
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << "INPUT GRAPH" << endl;

		Graph graph;
		cin >> graph;
		cout << graph;

		vector<vector<Edge> > newGraph;
		cout << "Kruskal's Algorithm is loading..." << endl;
		Kruskal::Algorithm(graph, newGraph);

		if (newGraph.size() == 0)
		{
			cout << "Graph don't have edges." << endl;
			return;
		}

		for (int i = 0; i < newGraph.size(); i++)
		{
			cout << endl << "Connection " << i << ": " << endl;

			for (int j = 0; j < newGraph[i].size(); j++)
				cout << newGraph[i][j] << endl;
		}

		newGraph.clear();
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}
}