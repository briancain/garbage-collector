#ifndef HEAPLIST_H
#define HEAPLIST_H

typedef struct HeapBlock {
  size_t size;
  int mark;
  void* heapPtr;
  struct HeapBlock* next;
  struct HeapBlock* prev;
} HeapBlock;

typedef struct HeapBlockList {
  int listSize;
  HeapBlock* first;
  HeapBlock* last;
} HeapBlockList;

HeapBlockList* initHeapList(void);
void addNewHeapBlock(HeapBlockList* list, size_t size, void* heapPtr);
void freeHeapBlockList(HeapBlockList* list);

#endif
