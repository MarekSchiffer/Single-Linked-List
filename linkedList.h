#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

typedef struct linked_list_s {
   struct node_s *head;
   struct node_s *tail;
   int size;
   void (*freeFn)(void*);
} linked_list_t;

typedef struct node_s {
   void *data;
   struct node_s* next;
} node_t;

typedef void (*ListMapFunction)(void *v1, void *v2);
typedef int (*ListCompareFunction)(const void *v1,const void *v2);

linked_list_t ListInit(void (*freeFn)(void*));
void ListDispose(linked_list_t *l);

int ListLength(linked_list_t *l);
void ListInsert(linked_list_t *l,void *elmAdr);
void ListRemove(linked_list_t *l,void **elmAdr);

void ListRemove_back(linked_list_t *l,void **elmAdr);
void ListInsert_front(linked_list_t *l,void *elmAdr);

void ListInsertNth(linked_list_t *l,void *elmAdr,int position);
void ListRemoveNth(linked_list_t *l,void **elmAdr,int position);
void ListReturnNth(linked_list_t *l,void **elmAdr, int position);

int ListFind(linked_list_t *l,void* elm,ListCompareFunction cmp,int startPosition);
void ListMap(linked_list_t *l,ListMapFunction m1,void *auxData);
void ListSort(linked_list_t *l,ListCompareFunction cmp);
#endif
