#ifndef PRIORITYQ_H
#define PRIORITYQ_H

#include "nodes.h"

typedef struct Heap {
	nodes *array;
	int front;
	int size;
} Heap;

void swap(nodes *x, nodes *y);

Heap makeHeap();

int isEmptyheap(Heap h);

void doubleHeapSize(Heap *hp);

void upheap(Heap *hp, int Front);

void downheap( Heap *hp, int n);

void enqueue(nodes n, Heap *hp);

nodes removeMax(Heap *hp);

#endif
