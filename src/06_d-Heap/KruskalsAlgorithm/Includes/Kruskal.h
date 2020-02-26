#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

#include <vector>

#include "DHeap.h"
#include "SeparatedSet.h"
#include "Edge.h"

using namespace std;

class Kruskal
{
private:
	static DHeap<Edge> CreateEdges(vector<vector<float> >);
	static vector<vector<float> > CreateGraph(DHeap<Edge>, int);

public:
	static vector<vector<float> > Algorithm(vector<vector<float> >);
};

#endif