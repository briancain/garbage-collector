#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heapList.h"
#include "list.h"
#include "gcLogger.h"

/*
 *  Program Pointer List file
 *
 *  Keeps track of all program pointers
 */

/*
 * Initialize a Ptr list
 */
ProgramPtrList* init() {
  ProgramPtrList* list = malloc(sizeof(ProgramPtrList));
  list->first = list->last = NULL;
  list->size = 0;

  return list;
}

/*
 * Free the memory list and
 * all of its neighbors
 */
void freeList(ProgramPtrList* list) {
  //logMsg("Free Memory");
  ProgramPtr* ptr;
  ProgramPtr* next;
  if (list->size == 0) {
    //logWarning("There is no ProgramPtr's in list to free");
    free(list);
  } else {
    //logMsg("Free Children Memory");
    for (ptr = list->first; ptr; ptr = next) {
      next = ptr->next;
      free(ptr);
    }
    free(list);
  }
}

/*
 *  [] => [] => + []
 *
 *  Push:
 *    [] => [] => => []
 */
void push(ProgramPtrList* list, void** addr, HeapBlock* heapBlock) {
  ProgramPtr* ptr = malloc(sizeof(ProgramPtr));

  ptr->varAddr = addr;
  // TODO: make sure heapblock is real
  ptr->heapBlock = heapBlock;
  ptr->heapParent = NULL;
  ptr->next = NULL;
  ptr->prev = NULL;

  if (list->size == 0) {
    list->first = ptr;
    list->last = ptr;
  } else {
    list->last->next = ptr;
    ptr->prev = list->last;
    list->last = ptr;
  }
  list->size++;
}

/*
 *  [] => []
 *
 *  Pop:
 *    []
 */
void pop(ProgramPtrList* list) {
  if (list->size == 0) {
    //throwError("List is empty");
  } else {
    //ProgramPtr* tmp = list->last;
    list->last = list->last->prev;
    list->size--;
  }
}
