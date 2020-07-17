#include <iostream>  
#include "graph.h"

using namespace std;
 


int main()
{

	char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	char edges[][2] = {
		{'A', 'B'}, 
		{'B', 'C'}, 
		{'B', 'E'}, 
		{'B', 'F'}, 
		{'C', 'E'}, 
		{'D', 'C'}, 
		{'E', 'D'}, 
		{'F', 'G'},
		{'G', 'E'}}; 
		int weight[] = {1, 2, 4, 1, 1, 3, 1, 1, 5};
	int vlen = sizeof(vexs)/sizeof(vexs[0]);
	int elen = sizeof(edges)/sizeof(edges[0]);

	GraphList<char> graph1(vexs, vlen, edges, elen, weight);
	graph1.printGraph();

	graph1.dijkstra();
	for(int i=0; i< 7; i++)
		graph1.printPath(vexs[i]);

	GraphMatrix<char> graph2(vexs, vlen, edges, elen, weight);
	graph2.printGraph();

	graph2.Kruskal();
	graph2.printTree();
	// cout << edges[1][1] << endl;

	return 0;
}
