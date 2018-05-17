#ifndef STATE_H
#define STATE_H

#include "define.h"

typedef struct {
	int cost;
	int *queens;
} State;

State makeState();

void printState(State s);

State* makePopulation(State *pool);

State* orderArray(State* ar);
#endif
