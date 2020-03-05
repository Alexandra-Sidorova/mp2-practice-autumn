#include <iostream>
#include <vector>
#include <time.h>

#include "exceptions.h"
#include "Includes/Dijkstra.h"
#include "Includes/Graph.h"

#define RANDOM 20

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	cout << "##### TEST DIJKSTRA'S ALGORITHMS #####" << endl;

	try
	{
		cout << endl << "CLASS EXAMPLE" << endl;
		
		vector<vector<float> > weights = { {-1},
										 {5, -1},
										 {8, 2, -1},
										 {11, -1, 3, -1},
										 {-1, 4, 2, -1, -1},
										 {-1, -1, -1, 8, 6, -1},
										 {-1, -1, -1, -1, -1, 13, -1},
										 {-1, -1, -1, -1, 1, 24, 5, -1} };

		Graph graph(weights);
		cout << graph;
		cout << "Start vertex = 0" << endl;
		float** result = Dijkstra::Algorithm(graph, 0);
		
		cout << "Shortest distances: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][0] << " ";

		cout << endl << "Previous vertices: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][1] << " ";
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << endl << "RANDOM GRAPH" << endl;

		int size = 6;
		int startV = rand() % size;

		vector<vector<float> > weights(size);

		for (int i = 0; i < size; i++)
		{
			weights[i].resize(i + 1);

			for (int j = 0; j < i; j++)
				weights[i][j] = rand() % RANDOM;

			weights[i][i] = -1;
		}

		Graph graph(weights);
		cout << graph;
		cout << "Start vertex = " << startV << endl;
		float** result = Dijkstra::Algorithm(graph, startV);

		cout << "Shortest distances: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][0] << " ";

		cout << endl << "Previous vertices: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][1] << " ";
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

		vector<vector<float> > weights(size);

		for (int i = 0; i < size; i++)
		{
			weights[i].resize(i + 1);

			for (int j = 0; j < i; j++)
				weights[i][j] = rand() % RANDOM;

			weights[i][i] = -1;
		}

		Graph graph(weights);
		cout << graph;
		cout << "Start vertex = " << startV << endl;
		float** result = Dijkstra::Algorithm(graph, startV);

		cout << "Shortest distances: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][0] << " ";

		cout << endl << "Previous vertices: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][1] << " ";
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}
}