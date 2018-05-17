/* listTypeAndFunctions.c, Gerard Renardel, 31 January 2018 */

#include <stdlib.h> 
#include <stdio.h>
#include <assert.h>

#include "list.h"
#include "state.h"

List newEmptyList() {
  return NULL;
}

int isEmptyList (List li) {
	return ( li==NULL );
}

void listEmptyError() {    
  printf("list empty\n");
  abort();
}

List addItem(State n, List li) {
  List newList = malloc(sizeof(struct ListNode));
  assert(newList!=NULL);
  newList->item = n;
  newList->next = li;
  return newList;
}

State firstItem(List li) {
  if ( li == NULL ) {
    listEmptyError();
  }
  return li->item;
}

List removeFirstNode(List li) {
  List returnList;
  if ( li == NULL ) {
    listEmptyError();
  }
  returnList = li->next;
  free(li->item.queens);
  free(li);
  return returnList;
}

void freeList(List li) {
  List li1;
  while ( li != NULL ) {
    li1 = li->next;
    free((li->item.queens));
    free(li);
    li = li1;
  }
  return;
}


void listTooShort() {    
  printf("List too short\n");
  abort();
}

State itemAtPos(List li, int p) {
  if ( li == NULL ) {
    listTooShort();
  }
  if ( p==0 ) {
    return firstItem(li);
  } else {
    return itemAtPos(li->next,p-1);
  }
}

List removeItemAtPos(List li, int p, State *s) {
  if ( li == NULL ) {
    listTooShort();
  }
  if ( p==0 ) {
    *s = firstItem(li);
    return removeFirstNode(li);
    
  } else {
	li->next = removeItemAtPos(li->next,p-1, s); 
    return li;
  }
}

List addItemAtPos(List li, State n, int p) {
  if ( p==0 ) {
    return addItem(n,li);
  }
  if ( li == NULL ) {
    listTooShort();
  }
  li->next = addItemAtPos(li->next,n,p-1);
  return li;
}

List addItemAtPosIt(List li, State n, int p) {
  List li1;
  if ( p==0 ) {
    return addItem(n,li);
  }
  li1 = li;
  while ( li1 != NULL && p>1 ) {
    li1 = li1->next;
    p--;
  }
  if ( li1 == NULL ) {
    listTooShort();
  }
  /* now li1 points to the node on position p-1 */
  li1->next = addItem(n,li1->next);
  return li;
}

List removeItem(List li, int n) {
  if ( li == NULL ) {
    return li;
  }
  if ( li->item.cost == n ) {
    return removeFirstNode(li);
  }
  li->next = removeItem(li->next,n);
  return li;
}

List removeItemIt(List li, int n) {
  List li1;
  if ( li == NULL) {
    return li;
  }
  if ( li->item.cost == n ) {
    return removeFirstNode(li);
  }
  li1 = li;
  while ( li1->next != NULL && (li1->next)->item.cost != n ) {
    li1 = li1->next;
  }
  if ( li1->next!=NULL ) {  /* so (li1->next)->item == n */
    li1->next = removeFirstNode(li1->next);
  }
  return li;
}

List insertInOrder(List li, State n) {
	if ( li==NULL || n.cost <= (li->item).cost ) {
		return addItem(n, li);
	}
	if((li->item).cost <= n.cost){
		li->next = insertInOrder(li->next, n);
	}
	return li;
}
