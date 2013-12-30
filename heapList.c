#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heapList.h"
#include "list.h"
#include "gcLogger.h"

/*
 *  HeapBlock and HeapBlockList
 *
 *    - A doubly linked list implementation
 *      for keeping track of all the pointers
 *      on the heap.
 */

/*
 *  Initialize the HeapBlockList list
 */
HeapBlockList* initHeapList() {
  HeapBlockList* list = malloc(sizeof(HeapBlockList));

  list->listSize = 0;
  list->first = list->last = NULL;
  return list;
}

/*
 *  Add a new heap block onto the list
 */
void addNewHeapBlock(HeapBlockList* list, size_t size, void* heapPtr) {
  HeapBlock* block = malloc(sizeof(HeapBlock));

  block->size = size;
  block->mark = 0;
  block->heapPtr = heapPtr;
  block->next = block->prev = NULL;

  if (list->listSize == 0) {
    list->first = block;
    list->last = block;
  } else {
    list->last->next = block;
    block->prev = list->last;
    list->last = block;
  }

  list->listSize++;
}

/*
 *  Free all memory in HeapBlockList
 */
void freeHeapBlockList(HeapBlockList* list) {
  HeapBlock* ptr;
  HeapBlock* next;
  if (list->listSize == 0) {
    //logWarning("There is no HeapBlock's in list to free");
    free(list);
  } else {
    //logMsg("Heap BlockList Children Memory");
    for (ptr = list->first; ptr; ptr = next) {
      next = ptr->next;
      free(ptr);
    }
    free(list);
  }
}
