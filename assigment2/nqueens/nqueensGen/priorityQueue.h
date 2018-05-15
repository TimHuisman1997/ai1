#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "list.h"
#include "state.h"

typedef struct {
	List list;
	List lastNode;
} PrioQueue;

PrioQueue newEmptyQueue ();

int isEmptyQueue (PrioQueue q);

void queueEmptyError ();

void enqueue (State n, PrioQueue *qp);

State removeMax(PrioQueue *qp);

void freeQueue (PrioQueue q);

#endif
