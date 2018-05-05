#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"
#include "fringe.h"
#include "list.h"

#define RANGE 1000000

Fringe insertValidSucc(Fringe fringe, Fringe prSt, int value, State state, int action, int cost) {
  State s;
  
  if ((value < 0) || (value > RANGE)) {
    /* ignore states that are out of bounds */
    return fringe;
  }
  
  for(int i = 0; i < prSt.insertCnt; i++){
	if(value == prSt.states[i].value){
	  /* ignore states that are already visited */
      return fringe;
	  }
  }
  s.value = value;
  s.action = state.action;
  addItem(action, s.action);
  printf("%d\n", isEmptyList(s.action));
   
  
  return insertFringe(fringe, s);
}


void search(int mode, int start, int goal) {
  Fringe fringe, prSt;
  State state;
  int goalReached = 0;
  int visited = 0;
  int value;
  List actions = newEmptyList();

  prSt = makeFringe(1);
  fringe = makeFringe(mode);
  state.value = start;
  state.action = newEmptyList();
  fringe = insertFringe(fringe, state);
  addItem(7, state.action);
  while (!isEmptyFringe(fringe)) {
    /* get a state from the fringe */
    fringe = removeFringe(fringe, &state);
    //printf("%d\n", state.action);
    prSt = insertFringe(prSt, state);
    visited++;
    /* is state the goal? */
    value = state.value;
    if (value == goal) {
      goalReached = 1;
      break;
    }
    
    /* insert neighbouring states */
    fringe = insertValidSucc(fringe, prSt, value+1, state, 1, 1); /* rule n->n + 1      */
    fringe = insertValidSucc(fringe, prSt, 2*value, state, 2, 2); /* rule n->2*n        */
    fringe = insertValidSucc(fringe, prSt, 3*value, state, 3, 2); /* rule n->3*n        */
    fringe = insertValidSucc(fringe, prSt, value-1, state, 4, 1); /* rule n->n - 1      */
    fringe = insertValidSucc(fringe, prSt, value/2, state, 5, 3); /* rule n->floor(n/2) */
    fringe = insertValidSucc(fringe, prSt, value/3, state, 6, 3); /* rule n->floor(n/3) */
  }
  
  actions = state.action;
  
  while(!isEmptyList(actions)){
	  printf("%d ", firstItem(actions));
  }
  printf("\n");
  if (goalReached == 0) {
    printf("goal not reachable ");
  } else {
    printf("goal reached ");
  }
  printf("(%d nodes visited)\n", visited);
  showStats(fringe);
  deallocFringe(fringe);  
}

int main(int argc, char *argv[]) {
  int start, goal, fringetype;
  if ((argc == 1) || (argc > 4)) {
    fprintf(stderr, "Usage: %s <STACK|FIFO|HEAP> [start] [goal]\n", argv[0]);
    return EXIT_FAILURE;
  }
  fringetype = 0;
  
  if ((strcmp(argv[1], "STACK") == 0) || (strcmp(argv[1], "LIFO") == 0)) {
    fringetype = STACK;
  } else if (strcmp(argv[1], "FIFO") == 0) {
    fringetype = FIFO;
  } else if ((strcmp(argv[1], "HEAP") == 0) || (strcmp(argv[1], "PRIO") == 0)) {
    fringetype = HEAP;
  }
  if (fringetype == 0) {
    fprintf(stderr, "Usage: %s <STACK|FIFO|HEAP> [start] [goal]\n", argv[0]);
    return EXIT_FAILURE;
  }

  start = 0;
  goal = 42;
  if (argc == 3) {
    goal = atoi(argv[2]);
  } else if (argc == 4) {
    start = atoi(argv[2]);
    goal = atoi(argv[3]);
  }

  printf("Problem: route from %d to %d\n", start, goal);
  search(fringetype, start, goal); 
  return EXIT_SUCCESS;
}
