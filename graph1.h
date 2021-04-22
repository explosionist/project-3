#ifndef _graph1_H_
#define _graph1_H_

#include <iostream>
#include <string>
#include "heap.h"
#include "Vertex.h"
//#include "heap.h"

using namespace std;



typedef struct NODE
{
	int v;
	float w;
	NODE* next;
}NODE;



class graph1
{
public :
	HEAP* heap;
	NODE** Adj;
	VERTEX* V;
	int direction;
	int size;
	int flag;
	int valid = -1;
	int findSource = -1;
	int findDestination = -1;

	graph1(int size, int direction);
	void initAdj(int U, int V, float W);
	void printFunction();
	void initDijkstra(int source);

	int Dijkstra(int source, int destination);



};


#endif 