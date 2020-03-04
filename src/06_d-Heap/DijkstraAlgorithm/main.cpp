#include <iostream>
#include <vector>

#include "exceptions.h"
#include "Includes/Dijkstra.h"
#include "Includes/Graph.h"

using namespace std;

void main()
{
	cout << "##### TEST DIJKSTRA'S ALGORITHMS #####" << endl;

	try
	{
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
		float** result = Dijkstra::Algorithm(graph, 0);
		
		cout << "Shortest distances: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][0] << ", ";

		cout << endl << "Previous vertices: " << endl;
		for (int i = 0; i < weights.size(); i++)
			cout << result[i][1] << ", ";
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}
}