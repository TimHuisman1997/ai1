#ifndef NQUEENSFUNC_H
#define NQUEENSFUNC_H

#include "define.h"


int inConflict(int row0, int column0, int row1, int column1) ;

int countConflicts(int *queens);

int inConflictWithAnotherQueen(int row, int col, int *queens);

void printBoard(int *queens);

#endif
