#include "linkedList.h"

linked_list_t ListInit(void (*freeFn)(void*)) {
  linked_list_t localList;
//  localList.head = malloc(sizeof(node_t));
  localList.head = NULL;
  localList.tail = NULL;
  localList.size = 0;
  localList.freeFn = freeFn;

  return localList;
}

void ListDispose(linked_list_t* l) {
  node_t* current = l->head;
  node_t* next;

  if (l->freeFn != NULL) {

    while(current != NULL) {
     l->freeFn(&current->data);

     next = current->next;
     free(current);
     current = next;
    }
  }
  else{
  while( current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  }

}

void ListInsert_front(linked_list_t* l, void* elmAdr) {
      node_t* newNode = malloc(sizeof(node_t));
      newNode->data = elmAdr;
      newNode->next = l->head;
      l->head = newNode;
      l->size +=1;

  if ( l->tail == NULL ) { l->tail = newNode; }
}

void ListInsert(linked_list_t* l, void* elmAdr) {

  if ( l->tail == NULL && l->size == 0) { ListInsert_front(l,elmAdr); return; }

  node_t* newNode = malloc(sizeof(node_t));
  newNode->data = elmAdr;
  newNode->next = NULL;

  (l->tail)->next = newNode;
  l->tail = newNode;
  l->size++;
}

void ListRemove(linked_list_t* l, void** elmAdr) {
  assert( l->head != NULL);

  if (elmAdr != NULL) {
    *elmAdr = (l->head)->data;
  }
  else {
  if (l->freeFn != NULL ) { l->freeFn(&(l->head)->data); }
  }

  if (l->head == l->tail) { l->tail = NULL; }

  node_t* next = (l->head)->next;
  free(l->head);
  l->head = next;
  l->size -=1;
}

void ListRemove_back(linked_list_t* l,void** elmAdr) {
  node_t* current = l->head;

  if ( elmAdr != NULL) { *elmAdr = (l->tail)->data; }
  else {
    if ( l->freeFn != NULL ) {
     l->freeFn(&(l->tail)->data);
    }
  }

  while (current->next != l->tail) {
    assert( (l->tail)->next == NULL);
    current = current->next;
  }

  free(l->tail);
  l->tail = current;
  current->next = NULL;
  l->size--;
}

int ListLength(linked_list_t* l) {
  return l->size;
}

int ListFind(linked_list_t* l,void* elm,ListCompareFunction cmp,int startPosition) {
  assert(l->head != NULL);

  node_t* current = l->head;

  int count = 0;
  while(current->next != NULL) { 
    if ( count > startPosition && cmp(&current->data,elm) == 0 ) { return count; }

    current=current->next;
    count++;
  }

  if ( current->next != NULL) { return count; }
  if ( current->next == NULL && cmp(&current->data,elm) == 0 ) { return count; }
  else return -1;


}

static void PopPosition(linked_list_t *l, node_t** n, void** elmAdr) {

  void* newNext = ((*n)->next)->next;

  if ( elmAdr != NULL ) {
  *elmAdr = ((*n)->next)->data;
  }

  if ( elmAdr == NULL && l->freeFn != NULL ) {
    l->freeFn(&(*n)->next->data);
  }

  free((*n)->next);
  (*n)->next = newNext;
}

void ListRemoveNth(linked_list_t *l,void** elmAdr, int position) {
  assert( 0<= position <= l->size);
  assert( l->head != NULL);
  assert( l->head != NULL);

  if (position == 0)         { ListRemove(l,elmAdr); return; }
  if (position == l->size) { ListRemove_back(l,elmAdr); return; }

  node_t* current = l->head;

  for(int i=0; i<position-1; i++) {
    current = current->next;
  }

  PopPosition(l,&current,elmAdr);
  l->size--;

  return;


}

static void PushPosition(node_t** n,void* Adr) {

  node_t* newNode = malloc(sizeof(node_t));
  newNode->data = Adr;
  newNode->next = (*n)->next;
  (*n)->next = newNode;

  return;
}

void ListInsertNth(linked_list_t* l,void* elmAdr, int position) {
  assert(0<= position <= l->size);

  if (position == 0)         { ListInsert_front(l,elmAdr); return; }
  if (position == l->size)   { ListInsert(l,elmAdr); return; }

  node_t* current = l->head;

  for(int i=0; i<position-1; i++) {
    current = current->next;
  }

  PushPosition(&current,elmAdr);
  l->size++;
}

void ListReturnNth(linked_list_t* l,void** elmAdr, int position) {
  assert(0<= position <= l->size);
  assert( l->head != NULL);

  node_t* current = l->head;

  for(int i=0; i<position; i++) {
    current = current->next;
  }

  *elmAdr = &current->data;

}

void ListMap(linked_list_t* l, ListMapFunction map,void* auxData) {
  node_t* current = l->head;
  while(current != NULL ) {
    map(&current->data,auxData);
    current=current->next;
  }
}

static void insert(const node_t* n, linked_list_t* l, ListCompareFunction cmp) {
  node_t* current = l->head;
  node_t* newNode = malloc(sizeof(node_t));
  newNode->data = n->data;

  if (current == NULL) {
      newNode->next = NULL;
      l->head = newNode;
      l->tail = newNode;
      l->size +=1;
      return;
  }

  if (cmp(&newNode->data,&current->data) <= 0) {
      newNode->next = l->head;
      l->head = newNode;
      l->size +=1;
    return;
  }

  while( current->next != NULL && cmp(&newNode->data,&(current->next)->data) > 0) {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;
  l->tail = newNode;

  l->size +=1;

  return;

}

void ListSort(linked_list_t* l,ListCompareFunction cmp) {
  linked_list_t sortedList = ListInit(l->freeFn);
  node_t* current = l->head;

  int i = 0;
  while ( current != NULL ) {
    i++;
    node_t* toInsert = malloc(sizeof(node_t));
    toInsert->data = current->data;
    insert(toInsert,&sortedList,cmp);
//    if ( i % 1000 == 0 ) {fprintf(stdout,"Still Sorting: %i\n",i); fflush(stdout); }

    node_t* saveCurrent = current;
    current = current->next;
    free(saveCurrent);
    free(toInsert);

  }

  l->head = sortedList.head;
  l->tail = sortedList.tail;
  l->size = sortedList.size;

  return;
}
