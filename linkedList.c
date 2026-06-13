#include "linkedlist.h"

typedef struct node_s {
  struct node_s *next;
  void *data;
} node_t;


void ListInit(linked_list_t *sll, size_t elmSize, sll_freeFn freeFn) {

  sll->head = NULL;
  sll->tail = NULL;
  sll->size = 0;
  sll->elmSize = elmSize;
  sll->fullNodeSize = sizeof(node_t) + sll->elmSize - sizeof(void*);
  sll->freeFn = (freeFn) ?  freeFn :  NULL;
}


void ListDispose(linked_list_t *sll) {

    node_t *current = sll->head;
    node_t *next_node = NULL;

    if (sll->freeFn) {
      for ( ; current ; ) {
      sll->freeFn(&current->data);

      next_node = current->next;
      free(current);
      current = next_node;
      }
    }
    else {
      for ( ; current ; ) {
        next_node = current->next;
        free(current);
        current = next_node;
      }
    }

    sll->head = NULL;
    sll->tail = NULL;
    sll->size = 0;
    sll->elmSize = 0;
    sll->fullNodeSize = 0;
    sll->freeFn = NULL;
}


#define SLL_INSERT_BACK(sll,elmAddr) \
  do { \
  node_t *new_node  = malloc( sll->fullNodeSize ); \
  new_node->next = NULL; \
  elmAddr ? memcpy(&new_node->data,elmAddr,sll->elmSize) : (void*)0; \
  sll->tail->next = new_node; \
  sll->tail = new_node; \
  ++sll->size; \
  } while(false);


#define SLL_INSERT_FRONT(sll,elmAddr)  \
  do { \
  node_t *new_node = malloc( sll->fullNodeSize ); \
  elmAddr ? memcpy(&new_node->data,elmAddr,sll->elmSize) : (void*)0; \
  new_node->next = sll->head; \
  if ( sll->head == NULL ) { sll->tail = new_node; } \
  sll->head = new_node; \
  ++sll->size; \
  } while(false);


#define SLL_REMOVE_FRONT(sll,elmAddr) \
  do { \
    elmAddr ? memcpy(elmAddr,&sll->head->data,sll->elmSize) : (void*)0; \
    node_t *tmp = sll->head->next; \
    (!elmAddr && sll->freeFn) ? sll->freeFn(&sll->head->data): (void*)0; \
    free(sll->head); \
    sll->head=tmp; \
    if (sll->head == NULL) { sll->tail = NULL; } \
    --sll->size; \
  } while(false);


#define SLL_REMOVE_BACK(sll,elmAddr) \
  do { \
    node_t **current = &sll->head; \
    for ( ; (*current)->next != sll->tail; current = &(*current)->next); \
    assert ( (*current)->next == sll->tail ); \
    elmAddr ? memcpy(elmAddr,&sll->tail->data,sll->elmSize) : (void*)0; \
    (!elmAddr && sll->freeFn) ? sll->freeFn(&sll->tail->data): (void*)0; \
    free(sll->tail); \
    sll->tail = *current; \
    (*current)->next = NULL; \
    --sll->size; \
  } while (false);


#define REMOVE_LAST_EXISTING_ELEMENT(sll,elmAddr) \
  do { \
  elmAddr ? memcpy(elmAddr, &sll->head->data,sll->elmSize) : (void*)0 ; \
  (!elmAddr && sll->freeFn) ? sll->freeFn(&sll->head->data): (void*)0; \
  free(sll->head); \
  sll->head = NULL; \
  sll->tail = NULL; \
  --sll->size; \
  } while(false);


#define INSERT_AT_POSITION(sll,current,elmAddr) \
  do { \
  node_t *new_node = malloc( sll->fullNodeSize ); \
  elmAddr ? memcpy(&new_node->data,elmAddr,sll->elmSize) : (void*)0; \
  new_node->next = (*current); \
  *current = new_node; \
  ++sll->size; \
  } while (false);


#define REMOVE_AT_POSITION(sll,current,elmAddr) \
  do { \
  elmAddr ? memcpy(elmAddr,&(*current)->data,sll->elmSize): (void*)0; \
  node_t *next = (*current)->next; \
  (!elmAddr && sll->freeFn) ? sll->freeFn(&(*current)->data): (void*)0; \
  free(*current); \
  *current = next; \
  --sll->size; \
  } while(false);


void remove_at_position(linked_list_t *sll, node_t **current, void *elmAddr) {
  elmAddr ? memcpy(elmAddr,&(*current)->data,sll->elmSize): (void*)0;
  node_t *next = (*current)->next;
  free(*current);
  *current = next;
  --sll->size;
}

void ListInsert(linked_list_t *sll, void *elmAddr) {
  if ( !sll->head && !sll->tail ) { SLL_INSERT_FRONT(sll,elmAddr); return; }
  SLL_INSERT_BACK(sll,elmAddr);
}


void ListInsert_front(linked_list_t *sll, void *elmAddr) {
  SLL_INSERT_FRONT(sll,elmAddr);
}


void ListRemove(linked_list_t *sll, void *elmAddr) {

  if (!sll->head) { return; }

  if ( sll->head->next ) { SLL_REMOVE_FRONT(sll,elmAddr); return; }
  REMOVE_LAST_EXISTING_ELEMENT(sll,elmAddr);
}


void ListRemove_back(linked_list_t *sll, void *elmAddr) {

  if ( !sll->head || !sll->tail ) { return; }

  if ( sll->head != sll->tail ) { SLL_REMOVE_BACK(sll,elmAddr); return; }
  REMOVE_LAST_EXISTING_ELEMENT(sll,elmAddr);
 }


void ListInsertNth(linked_list_t *sll, void *elmAddr, size_t pos) {

  if ( pos == 0 ) { SLL_INSERT_FRONT(sll,elmAddr); return; }

  node_t **current = &sll->head;
  for ( size_t k=0; k<pos; ++k, current = &(*current)->next);
  if ( !(*current) ) { SLL_INSERT_BACK(sll,elmAddr); return; }

  INSERT_AT_POSITION(sll,current,elmAddr);
}


void ListRemoveNth(linked_list_t *sll, void *elmAddr, size_t pos) {

  if ( sll->size < pos || pos > sll->size-1 ) { return; }
  if ( pos == 0 ) { SLL_REMOVE_FRONT(sll,elmAddr); return; }
  if ( pos == (sll->size-1) ) { SLL_REMOVE_BACK(sll,elmAddr); return; }

  node_t **current = &sll->head;
  for ( size_t k=0; k<pos ; ++k ) { current = &(*current)->next; }
  REMOVE_AT_POSITION(sll,current,elmAddr);
}


size_t ListLength(linked_list_t *sll) {
return sll->size;
}


void ListReturnNth(linked_list_t *sll, void **elmAddr, size_t pos) {

  if ( pos < 0 || pos >= sll->size ) { return; }

  node_t *current = sll->head;
  for ( size_t k=0 ; k<pos ; ++k ) { current = current->next; }
  elmAddr ? *elmAddr = &current->data: (void*)0;

}


void ListMap(linked_list_t *sll, sll_mapFn mapFn, void *ext) {

  node_t *current = sll->head;

  for ( ; current ; current=current->next ) {
    mapFn(&current->data,ext);
  }
}


int32_t ListFind(linked_list_t *sll, void *elmAddr, sll_cmpFn cmpFn, uint32_t start_position) {

  if ( start_position > sll->size || start_position < 0 ) { return -1; }

  node_t *current = sll->head;

  if ( start_position > 0 ) { 
    for ( size_t k=0; k<=start_position && current; ++k, current=current->next );
  }

  if ( !current ) { return -1; }

  int32_t cmp_result=0;
  size_t position = (start_position == 0) ? start_position : start_position+1;
  for ( ; current ; ++position ) {
    cmp_result = cmpFn( &current->data, elmAddr );
    if ( cmp_result == 0 ) {
      return position;
    }
    current = current->next;
  }

  return -1;
}


static void insert_sorted(linked_list_t *sorted_list, node_t **to_insert_node, sll_cmpFn cmpFn) {

  node_t **current = &sorted_list->head;

  if ( sorted_list->size == 0 ) {  SLL_INSERT_FRONT(sorted_list,&(*to_insert_node)->data); return; }
  int32_t cmp_result=0;

  for ( ; *current ; current = &(*current)->next ) {
    cmp_result = cmpFn( &(*current)->data, &(*to_insert_node)->data);
    if ( cmp_result >= 0 ) { INSERT_AT_POSITION(sorted_list,current,&(*to_insert_node)->data); return; }
  }

  SLL_INSERT_BACK(sorted_list,&(*to_insert_node)->data);
}



void ListSort(linked_list_t *sll, sll_cmpFn cmpFn) {
  linked_list_t sorted_list;
  ListInit(&sorted_list,sll->elmSize,sll->freeFn);

  node_t **current = &sll->head;

  for ( ; *current; ) {
    insert_sorted(&sorted_list,current,cmpFn);
    node_t *tmp = (*current)->next;
    free(*current);
    *current = tmp;
  }

  sll->head = sorted_list.head;
  sll->tail = sorted_list.tail;

}
