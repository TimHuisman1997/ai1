/* listTypeAndFunctions.c, Gerard Renardel, 31 January 2018 */


#include <stdlib.h> 
#include <stdio.h>
#include <assert.h>
#include "nodes.h"

typedef struct ListNode* List;

int Equalstruct(Node A, Node B){
	if((A.f == B.f)&&(A.h == B.h)&&(A.g == B.g)&& (A.x == B.x)&& (A.y == B.y) ){
		return 1;
	}
	return 0;
}

struct ListNode {
  Node item;
  List next;
};

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

List addItem(Node n, List li) {
  List newList = malloc(sizeof(struct ListNode));
  assert(newList!=NULL);
  newList->item = n;
  newList->next = li;
  return newList;
}

Node firstItem(List li) {
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
  free(li);
  return returnList;
}

void freeList(List li) {
  List li1;
  while ( li != NULL ) {
    li1 = li->next;
    free(li);
    li = li1;
  }
  return;
}

void listTooShort() {    
  printf("List too short\n");
  abort();
}

int visitListRec(List li) {
  if (li == NULL) {
    return 0;
  }
  visitListRec(li->next);
  return 1;
}

Node itemAtPos(List li, int p) {
  if ( li == NULL ) {
    listTooShort();
  }
  if ( p==0 ) {
    return firstItem(li);
  } else {
    return itemAtPos(li->next,p-1);
  }
}

List addItemAtPos(List li, Node n, int p) {
  if ( p==0 ) {
    return addItem(n,li);
  }
  if ( li == NULL ) {
    listTooShort();
  }
  li->next = addItemAtPos(li->next,n,p-1);
  return li;
}

List addItemAtPosIt(List li, Node n, int p) {
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

List removeItem(List li, Node n) {
  if ( li == NULL ) {
    return li;
  }
  if (Equalstruct(li->item, n)) {
    return removeFirstNode(li);
  }
  li->next = removeItem(li->next,n);
  return li;
}

List removeItemIt(List li, Node n) {
  List li1;
  if ( li == NULL) {
    return li;
  }
  if ( Equalstruct(li->item, n)) {
    return removeFirstNode(li);
  }
  li1 = li;
  while ( li1->next != NULL && !Equalstruct((li1->next)->item, n) ) {
    li1 = li1->next;
  }
  if ( li1->next!=NULL ) {  /* so (li1->next)->item == n */
    li1->next = removeFirstNode(li1->next);
  }
  return li;
}
