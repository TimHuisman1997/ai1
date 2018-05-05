#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "nodes.h"
#include "priorityQ.h"


void swap(nodes *x, nodes *y){
	
	nodes* temp;
	
	temp = x; 
	x = y; 
	y= temp;
}


Heap makeHeap(){
	Heap h;
	h.array = malloc(1*sizeof(int));
	assert(h.array!=NULL);
	h.front = 1;
	h.size = 1;	
	return h;
}

int isEmptyheap(Heap h){
	return (h.front == 1);
}

void doubleHeapSize(Heap *hp){
	int newSize = 2*hp->size;
	hp->array = realloc(hp->array, newSize*sizeof(nodes));
	assert(hp->array != NULL);
		hp->size = newSize;
}

void upheap(Heap *hp, int Front){
	if(Front > 1 && hp->array[Front].f > hp->array[Front/2].f){
		swap(&(hp->array[Front]),&(hp->array[Front/2]));
		upheap(hp, Front/2);
	}
}

void downheap( Heap *hp, int n){
	int Front = hp->front;
	int indexMax= n;
	if (Front <2*n+1){
		return;
	}
	if (hp->array[n].f < hp->array[2*n].f){
		indexMax = 2*n;
	}
	if (Front > 2*n+1 && hp->array[indexMax].f < hp->array[2*n+1].f){
		indexMax = 2*n +1;
	}
	if(indexMax != n){
				swap(&(hp->array[n]),&(hp->array[indexMax]));
		downheap(hp,indexMax);
		}
		
}


void enqueue(nodes n, Heap *hp){
	int Front = hp->front;
	if(Front == hp->size){
		doubleHeapSize(hp);
	}
	hp->array[Front] = n;
	downheap(hp, 1);
	hp->front = Front + 1;
}


nodes removeMax(Heap *hp){
	nodes n;
	if(isEmptyheap(*hp)){
		abort();
	}
	n = hp->array[1];
	hp->front--;
	hp->array[1] = hp->array[hp->front];
	upheap(hp,hp->front);
	return n;
}



















