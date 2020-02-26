#include <iostream>
#include <vector>

#include "exceptions.h"
//#include "Includes/Kruskal.h"

using namespace std;

void main()
{
	cout << "##### TEST KRUSKAL'S ALGORITHMS #####" << endl;

	try
	{
		vector<vector<float> > graph = { {-1}, 
										 {8, -1}, 
		                                 {-1, 10, -1}, 
		                                 {-1, 1, 5, -1}, 
		                                 {3, 0, 2, 4, -1}, 
		                                 {-1, 2, 9, -1, -1, -1} };

		for (int i = 0; i < graph.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				cout << graph[i][j] << "\t";
			}
			cout << endl;
		}

		//vector<vector<float> > graph
	}
	catch (Exception ex)
	{
		cout << ex.what() << endl << endl;
	}
}