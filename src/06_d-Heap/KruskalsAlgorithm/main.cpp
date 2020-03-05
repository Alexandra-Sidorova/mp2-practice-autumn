#include <iostream>
#include <vector>
#include <time.h>

#include "exceptions.h"
#include "Includes/Kruskal.h"
#include "Includes/Graph.h"

#define RANDOM 15

using namespace std;

void main()
{
	srand((unsigned int)time(0));

	cout << "##### TEST KRUSKAL'S ALGORITHMS #####" << endl;

	try
	{
		cout << endl <<"CLASS EXAMPLE" << endl;
		
		vector<vector<float> > weights = { {-1},
										 {8, -1},
										 {-1, 10, -1},
										 {-1, 1, 5, -1},
										 {3, 0, 2, 4, -1},
										 {2, 2, 9, -1, -1, -1} };

		Graph graph(weights);
		cout << graph;
		Graph newGraph = Kruskal::Algorithm(graph);
		cout << newGraph;
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}

	try
	{
		cout << endl << "RANDOM GRAPH" << endl;

		int size = 5;

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
		Graph newGraph = Kruskal::Algorithm(graph);
		cout << newGraph;
	}
	catch (Exception ex)
	{
		cout << "[ERROR] " << ex.what() << endl << endl;
	}
}