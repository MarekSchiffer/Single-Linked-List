#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct _list {
   struct _node* head;
   struct _node* tail;
   int size;
   void (*freeFn)(void*);
} list;

typedef struct _node {
   void* data;
   struct _node* next;
} node;

typedef void (*ListMapFunction)(void* v1, void* v2);
typedef int (*ListCompareFunction)(const void* v1,const void* v2);

list ListInit(void (*freeFn)(void*));
void ListDispose(list* l);

int ListLength(list* l);
void ListInsert(list* l,void* elmAdr);
void ListRemove(list* l,void** elmAdr);

void ListRemove_back(list* l,void** elmAdr);
void ListInsert_front(list* l,void* elmAdr);

void ListInsertNth(list* l,void* elmAdr,int position);
void ListRemoveNth(list* l,void** elmAdr,int position);
void ListReturnNth(list*,void** elmAdr, int position);

int ListFind(list* l,void* elm,ListCompareFunction cmp,int startPosition);
void ListMap(list* l,ListMapFunction m1,void* auxData);
void ListSort(list* l,ListCompareFunction cmp);
#endif
