#define _CRT_SECURE_NO_WARNINGS
#include "heap.h"
#include <iostream>
#include <string.h>

using namespace std;

HEAP* initialize(int n)
{
	HEAP* tempHeap = new HEAP;			//dynamically assign memory to tempHeap
	tempHeap->capacity = n;
	tempHeap->size = 0;
	tempHeap->H = new ElementT[n + 1];	//allocate memory to ElementT with a size of n + 1 and H can point to it

	return tempHeap;
}


int Insert(HEAP* heap, ELEMENT* element, VERTEX* V, int flag)
{
	heap->size++;
	int i = heap->size;
	heap->H[i] = element;

	V[heap->H[i]->vertex].pos = i;

	MovingUp(heap, i, V);

	if (flag == 1)
	{
		printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->distance);	// print the insertion
	}

	return 0;
}


int ExtractMin(HEAP* heap, VERTEX* V, int flag)
{
	int nodeName = heap->H[1]->vertex;
	V[nodeName].d = heap->H[1]->distance;
	V[nodeName].pos = NULL;

	
	delete(heap->H[1]);		// delete the min node from the heap
	if (flag == 1)
	{
		printf("Delete vertex %d, key=%12.4f\n", nodeName, V[nodeName].d);	// print the deletion
	}


	if (heap->size == 1) 
	{
		heap->size--;
		return nodeName;
	}
	heap->H[1] = heap->H[heap->size];
	V[heap->H[1]->vertex].pos = 1;
	heap->size--;

	min_Heapify(heap, 1, V);

	return nodeName;
}


int DecreaseKey(HEAP* heap, int pos, float newDistance, VERTEX* V, int flag)
{
	if (pos <1 || pos>heap->size || newDistance >= heap->H[pos]->distance)
	{
		printf("Error in DecreaseKey\n");
		return 1;
	}

	float oldDistance = heap->H[pos]->distance;
	heap->H[pos]->distance = newDistance;
	MovingUp(heap, pos, V);

	if (flag == 1)
	{
		printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", heap->H[pos]->vertex, oldDistance, newDistance);	// print the node decreasing
	}

	return 0;
}


void MovingUp(HEAP* heap, int pos, VERTEX* V)
{
	int parent;
	ElementT temp;

	parent = pos / 2;

	if (pos > 1 && heap->H[pos]->distance < heap->H[parent]->distance)
	{
		temp = heap->H[pos];
		heap->H[pos] = heap->H[parent];
		heap->H[parent] = temp;
		V[heap->H[pos]->vertex].pos = pos;
		V[heap->H[parent]->vertex].pos = parent;
		MovingUp(heap, parent, V);
	}
}


void min_Heapify(HEAP* heap, int index, VERTEX* V)
{

	int smallest = index; // Initialize smallest as root 
	int l = 2 * index;
	int r = 2 * index + 1;

	// If left child is smaller than root 
	if (l <= heap->size && heap->H[l]->distance < heap->H[smallest]->distance)
		smallest = l;

	// If right child is smaller than root 
	if (r <= heap->size && heap->H[r]->distance < heap->H[smallest]->distance)
		smallest = r;

	// If smallest is not root 
	if (smallest != index) {
		swap(heap->H[index], heap->H[smallest]);

		//V[heap->H[smallest]->vertex].pos = smallest;
		//V[heap->H[index]->vertex].pos = index;

		min_Heapify(heap, smallest, V);
	}
}


void deleteHeap(HEAP* heap)
{
	if (heap != NULL)
	{
		delete heap->H;
		delete heap;
		heap = NULL;
	}
}
