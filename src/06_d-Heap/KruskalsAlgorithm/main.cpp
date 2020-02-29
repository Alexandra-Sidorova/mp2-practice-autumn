#include <iostream>
#include <vector>

#include "exceptions.h"
#include "Includes/Kruskal.h"
#include "Includes/Graph.h"

using namespace std;

void main()
{
	cout << "##### TEST KRUSKAL'S ALGORITHMS #####" << endl;

	try
	{
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
		cout << ex.what() << endl << endl;
	}
}