#ifndef STATE_H
#define STATE_H

#include "list.h"

/* The type State is a data type that represents a possible state 
 * of a search problem. It can be a complicated structure, but it 
 * can also be a simple type (like int, char, ..). 
 * Note: if State is a structure, make sure that the structure does not 
 *       contain pointers!
 */

typedef struct {
  int value;
  List action;
} State;

#endif

