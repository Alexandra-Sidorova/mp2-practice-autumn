#include <iostream>
#include <vector>
#include <time.h>

#include "exceptions.h"
#include "Dijkstra.h"
#include "Graph.h"

#define RANDOM 20

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	cout << "##### TEST DIJKSTRA'S ALGORITHMS #####" << endl;

	try
	{
		cout << endl << "CLASS EXAMPLE" << endl;
		
		int size = 8;
		float weights[64] = { -1, 5, 8, 11, -1, -1, -1, -1,
							   5, -1, 2, -1, 4, -1, -1, -1,
							   8, 2, -1, 3, 2, -1, -1, -1,
							   11, -1, 3, -1, -1, 8, -1, -1,
							   -1, 4, -1, -1, -1, 6, -1, 1,
							   -1, -1, -1, 8, 6, -1, 13, 24,
							   -1, -1, -1, -1, -1, 13, -1, 5,
							   -1, -1, -1, -1, 1, 24, 5, -1 };

		Graph graph(weights, 8);
		cout << graph;
		cout << "Start vertex = 0" << endl;
		vector<vector<int> > paths;
		float* result = new float[size];
		cout << "Dijkstra's Algorithm is loading..." << endl;
		Dijkstra::Algorithm(graph, 0, paths, result);
		
		for (int i = 0; i < size; i++)
		{
			cout << "Vertex - " << i << " Distance - " << result[i] << " Path: [ ";
			for (auto iter = paths[i].begin(); iter != paths[i].end(); ++iter)
				cout << *iter << " ";

			cout << "]" << endl;
		}
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}

	/*try
	{
		cout << endl << endl << "RANDOM GRAPH" << endl;

		int size = 6;
		int startV = rand() % size;

		Graph graph(size);
		graph.GenerateConnectGraph();
		cout << graph;
		cout << "Start vertex = " << startV << endl;
		vector<vector<int> > paths;
		float* result = Dijkstra::Algorithm(graph, startV, paths);

		for (int i = 0; i < size; i++)
		{
			cout << "Vertex - " << i << " Distance - " << result[i] << " Path: [ ";
			for (auto iter = paths[i].begin(); iter != paths[i].end(); ++iter)
				cout << *iter << " ";

			cout << "]" << endl;
		}
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << endl << "INCORRECT START VERTEX" << endl;

		int size = 4;
		int startV = -5;

		Graph graph(size);
		graph.GenerateConnectGraph();
		cout << graph;
		cout << "Start vertex = " << startV << endl;
		vector<vector<int> > paths;
		float* result = Dijkstra::Algorithm(graph, startV, paths);

		for (int i = 0; i < size; i++)
		{
			cout << "Vertex - " << i << " Distance - " << result[i] << " Path: [ ";
			for (auto iter = paths[i].begin(); iter != paths[i].end(); ++iter)
				cout << *iter << " ";

			cout << "]" << endl;
		}
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}*/
}