#pragma once
#include <string.h>
#include "Vertex.h"
using namespace std;

typedef struct TAG_ELEMENT
{
	int vertex;
	float distance; 
}ELEMENT;

typedef ELEMENT* ElementT;

typedef struct TAG_HEAP
{
	int capacity;
	int size;
	ElementT* H;
}HEAP;

HEAP* initialize(int n);

void MovingUp(HEAP* heap, int pos, VERTEX* V);
int Insert(HEAP* heap, ELEMENT* element, VERTEX* V, int flag);
int ExtractMin(HEAP* heap, VERTEX* V, int flag);
int DecreaseKey(HEAP* heap, int index, float newDistance, VERTEX* V, int flag);
void min_Heapify(HEAP* heap, int index, VERTEX* V);

void deleteHeap(HEAP* heap);





