#include <stdlib.h>
#include <stdio.h>

#include "state.h"
#include "list.h"
#include "priorityQueue.h"

PrioQueue newEmptyQueue () {
	PrioQueue q;
	q.list = newEmptyList();
	q.lastNode = NULL;
	return q;
}

int isEmptyQueue (PrioQueue q){
	return isEmptyList(q.list);
}

void queueEmptyError () {
	printf("queue empty\n");
	exit(0);
}

void enqueue (State n, PrioQueue *qp) {
		qp->list = insertInOrder(qp->list, n);
		qp->lastNode = qp->list;
}

State removeMax(PrioQueue *qp){
	State n; 
	if(isEmptyQueue(*qp)){
		queueEmptyError();
	}
	n = firstItem(qp->list);
	qp->list = removeFirstNode(qp->list);
	if(isEmptyList(qp->list)){
		qp->lastNode = NULL;
	}
	return n;
}

void freeQueue (PrioQueue q){
	freeList(q.list);
}




