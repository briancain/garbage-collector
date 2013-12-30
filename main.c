#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "garbageCollector.h"
// #include "heapList.h"
// #include "list.h"
// #include "gcLogger.h"

/*
 *  Unit Test file
 */

// void pop_empty_list() {
//   runTest("Run Test pop_empty_list");
//   ProgramPtrList* list = init();
//   pop(list);
//   // free(list);
//   freeList(list);
// }
// 
// void pop_single() {
//   runTest("Run Test pop_single");
//   ProgramPtrList* list = init();
//   push(list, "Data", NULL);
//   push(list, "Data Pop", NULL);
// 
//   printf("List Size Before Pop: %d\n", list->size);
//   printf("List Last Val: %s\n", list->last->varAddr);
//   pop(list);
//   printf("List Size After Pop: %d\n", list->size);
//   printf("List Last Val: %s\n", list->last->varAddr);
// 
//   freeList(list);
// }
// 
// void push_single() {
//   runTest("Run Test push_single");
//   ProgramPtrList* list = init();
//   push(list, "Data", NULL);
//   printf("Count: %d\n", list->size);
//   printf("Value: %s\n", list->first->varAddr);
//   freeList(list);
// }
// 
// void push_double() {
//   runTest("Run Test push_double");
//   ProgramPtrList* list = init();
//   push(list, "Data", NULL);
//   printf("Count: %d\n", list->size);
//   printf("Value: %s\n", list->first->varAddr);
//   push(list, "Data 2", NULL);
//   printf("Count: %d\n", list->size);
//   printf("Value: %s\n", list->first->next->varAddr);
//   freeList(list);
// }

void init_hook(int heapSize) {
  runTest("Run test init_hook", 1);
  gcInit(heapSize, 1);
  gcDestroy();
}

void alloc_hook(int heapSize, int ptrSize) {
  runTest("Run test alloc_hook", 1);
  gcInit(heapSize, 1);
  //gcAlloc(sizeof(int)*ptrSize);
  gcDestroy();
}

void ptr_no_heap() {
  runTest("Run test ptr_no_heap", 1);

  void* mem = NULL; 
  if (mem == NULL) {
    throwError("Memory is NULL. Allocation Failed", 1);
  }
}

void no_space() {
  runTest("Running test no_space", 1);
  gcInit(5, 1);
  //gcAlloc(10);
  gcDestroy();
}

void herp_derp_heap() {
  runTest("Running test herp_derp_heap", 1);

  void* heap = malloc(100);

  void* ptr = heap;

  printf("ProgramPtr mem: %p\n", ptr);
  ptr++;
  printf("ProgramPtr mem+1: %p\n", ptr);
  free(heap);
}

void heap_chunk() {
  runTest("Running test heap_chunk", 1);
  gcInit(50, 1);
  int* mem = gcAlloc(sizeof(int)*10, &mem, NULL);
  printf("Mem space is: %p\n", mem);

  int i;
  for (i = 0; i < 10; i++) {
    mem[i] = i;
    printf("mem[%d]: %d\n", i, mem[i]);
  }
  gcDestroy();
}

void heap_test_equality() {
  runTest("Running test heap_test_equality", 1);
  // b = a
  gcInit(50, 1);
  int* a = gcAlloc(sizeof(int)*10, &a, NULL);
  int* b;
  printf("a space is: %p\n", a);

  int i;
  for (i = 0; i < 10; i++) {
    a[i] = i;
    printf("a[%d]: %d\n", i, a[i]);
  }

  b = a;
  gcReg(&b, NULL, NULL, 0);

  printf("b space is: %p\n", a);

  for (i = 0; i < 10; i++) {
    printf("b[%d]: %d\n", i, b[i]);
  }
  gcDestroy();
}

void force_gc() {
  runTest("Running test force_gc", 1);
  gcInit(20, 1);
  void* mem = gcAlloc(15, &mem, NULL);
  void* omg = gcAlloc(6, &omg, NULL);

  gcDestroy();
}

void test_gc_functionality() {
  runTest("Running test test_gc_functionality", 1);
  size_t heapSize = ((sizeof(int)*5)*2);
  gcInit(heapSize, 1);
  int* a = gcAlloc(sizeof(int)*5, &a, NULL);
  int* b = gcAlloc(sizeof(int)*5, &b, NULL);

  int i;
  for (i = 0; i < 5; i++) {
    b[i] = i;
    printf("b[%d] = %d\n", i, b[i]);
  }
  a = NULL;
  gcReg(&a, NULL, NULL, 0);

  int* c = gcAlloc(sizeof(int)*5, &c, NULL);

  for (i = 0; i < 5; i++) {
    printf("b[%d] = %d\n", i, b[i]);
  }

  gcDestroy();
}

void test_gc_multiple_arr() {
  runTest("Running test test_gc_multiple_arr", 1);
  int heapSize = ((sizeof(int)*5)*4);
  gcInit(heapSize, 1);

  int* a = gcAlloc(sizeof(int)*5, &a, NULL);
  int* b = gcAlloc(sizeof(int)*5, &b, NULL);
  int* c = gcAlloc(sizeof(int)*5, &c, NULL);
  int* d = gcAlloc(sizeof(int)*5, &d, NULL);

  int i;
  for (i = 0; i < 5; i++) {
    a[i] = 1;
    b[i] = 2;
    c[i] = 3;
    d[i] = 4;
  }

  printf("Address: %p\n", a);
  for (i = 0; i < 5; i++) {
    printf("a[%d] = %d\n", i, a[i]);
  }
  printf("\n");


  printf("Address: %p\n", b);
  for (i = 0; i < 5; i++) {
    printf("b[%d] = %d\n", i, b[i]);
  }
  printf("\n");


  printf("Address: %p\n", c);
  for (i = 0; i < 5; i++) {
    printf("c[%d] = %d\n", i, c[i]);
  }
  printf("\n");

  printf("Address: %p\n", d);
  for (i = 0; i < 5; i++) {
    printf("d[%d] = %d\n", i, d[i]);
  }
  printf("\n");

  b = NULL;
  gcReg(&b, NULL, NULL, 0);

  int* e = gcAlloc(sizeof(int)*5, &e, NULL);

  printf("Address: %p\n", a);
  for (i = 0; i < 5; i++) {
    printf("a[%d] = %d\n", i, a[i]);
  }
  printf("\n");

  printf("Address: %p\n", c);
  for (i = 0; i < 5; i++) {
    printf("c[%d] = %d\n", i, c[i]);
  }
  printf("\n");

  printf("Address: %p\n", d);
  for (i = 0; i < 5; i++) {
    printf("d[%d] = %d\n", i, d[i]);
  }
  printf("\n");

  gcDestroy();
}

void reachability_gc(size_t heapS) {
  runTest("Running test reachability", 1);

  typedef struct B {
    int x;
  } B;

  typedef struct A {
    B* b;
  } A;

  size_t heapSize = (sizeof(A)+sizeof(B));
  size_t derpSize = 131049;
  gcInit(1000000, 0);

  printf("Allocation\n");
  A* a = gcAlloc(sizeof(A), &a, NULL);
  printf("Allocation of a: %p\n", a);
  printf("About to set a member in struct a\n");
  a->b = gcAlloc(sizeof(B), &(a->b), &a);
  printf("About to set a var\n");
  a->b->x = 0;
  printf("a->b->x: %d\n", a->b->x);
  a = gcAlloc(sizeof(A), &a, NULL);
  a->b = gcAlloc(sizeof(B), &(a->b), &a);
  a->b->x = 100;

  printf("a->b->x: %d\n", a->b->x);

  gcDestroy();
}

/**
 *  Main tests
 */
int main(int argc, const char *argv[])
{
  size_t heapSize;
  int logging;

  if (argc <= 1) {
    logWarning("No CLI arguments given, using default heap size 100.", logging);
    heapSize = 1000;
  } else {
    heapSize = atol(argv[1]);
    int log = atoi(argv[2]);
    printf("Log: %d\n", log);
    logging = (log ? 1 : 0);
    printf("Heap size from CLI: %d\n", heapSize);
    printf("Logging: %d\n", logging);
  }

  logMsg("Running Tests", logging);
  printf("------------------\n");

  // Doubly Linked List Unit Tests
  // pop_empty_list();
  // push_single();
  // push_double();
  // pop_single();

  // Garbage Collector Unit Tests
  // init_hook(heapSize);
  // alloc_hook(heapSize, 5);
  // ptr_no_heap(); // breaking test
  // no_space(); // breaking test
  // herp_derp_heap();
  heap_chunk();
  heap_test_equality();
  // force_gc();
  test_gc_functionality();
  test_gc_multiple_arr();
  reachability_gc(heapSize);
  return 0;
}
