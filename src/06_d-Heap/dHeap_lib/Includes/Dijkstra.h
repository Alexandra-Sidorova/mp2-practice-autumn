#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Graph.h"

#include <vector>

class Dijkstra
{
public:
	static void Algorithm(const Graph&, const int, vector<vector<int> >&, float*); // .., start, paths, result
};

#endif