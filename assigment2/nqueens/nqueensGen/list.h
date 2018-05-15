#ifndef LIST_H
#define LIST_H

#include "state.h"

typedef struct ListNode* List;

struct ListNode {
  State item;
  List next;
};

List newEmptyList();

int isEmptyList (List li);

void listEmptyError();

List addItem(State n, List li);

State firstItem(List li);

List removeFirstNode(List li);

void freeList(List li);

void visit(List li);

void visitList(List li);

void visitListRec(List li);

void listTooShort();

State itemAtPos(List li, int p);

List removeItemAtPos(List li, int p, State *s);

List addItemAtPos(List li, State n, int p);

List addItemAtPosIt(List li, State n, int p);

List removeItem(List li, int n);

List removeItemIt(List li, int n);

List insertInOrder(List li, State n);

#endif
