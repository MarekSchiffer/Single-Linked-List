#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef void (*sll_freeFn)(void *elmAddr);
typedef void (*sll_mapFn)(void *elmAddr_1, void *elmAddr_2);
typedef int (*sll_cmpFn)(const void *elmAddr_1, const void *elmAddr_2);

typedef struct node_s node_t;

typedef struct linked_list_s {
  node_t *head;
  node_t *tail;
  size_t fullNodeSize;
  size_t elmSize;
  size_t size;
  sll_freeFn freeFn;
} linked_list_t;

void ListInit(linked_list_t *sll, size_t elmSize, sll_freeFn freeFn); 
void ListDispose(linked_list_t *sll);

size_t ListLength(linked_list_t *sll);
void ListInsert(linked_list_t *sll, void *elmAddr);
void ListRemove(linked_list_t *sll, void *elmAddr);

void ListRemove_back(linked_list_t *sll, void *elmAddr);
void ListInsert_front(linked_list_t *sll, void *elmAddr);

void ListInsertNth(linked_list_t *sll, void *elmAddr, size_t pos);
void ListRemoveNth(linked_list_t *sll, void *elmAddr, size_t pos);
void ListReturnNth(linked_list_t *sll, void **elmAddr, size_t pos);

int32_t ListFind(linked_list_t *sll, void *elmAddr, sll_cmpFn cmpFn, uint32_t start_position);
void ListMap(linked_list_t *sll, sll_mapFn mapFn, void *ext);
void ListSort(linked_list_t *sll, sll_cmpFn cmpFn);
#endif
