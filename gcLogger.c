/*
 *  Garbage Collector Logger
 *
 *    - A logging system for the GC.
 *
 *  Brian Cain
 */

#include <stdio.h>
#include "gcLogger.h"

void throwError(char* err, int log) {
  if (log) {
    fprintf(stderr, "\x1B[31m[GCErr] - %s\n", err);
    printf("\x1b[0m");
  }
}

void logWarning(char* msg, int log) {
  if (log) {
    printf("\x1B[33m[GCWrn] - %s\n", msg);
    printf("\x1b[0m");
  }
}

void logMsg(char* msg, int log) {
  if (log) {
    printf("\x1B[0m[GCMsg] - %s\n", msg);
  }
}

void runTest(char* msg, int log) {
  if (log) {
    printf("\x1B[32m[GCTst] - %s\n", msg);
    printf("\x1b[0m");
  }
}

void debug(char* msg, int log) {
  if (log) {
    printf("\x1B[34m[GCDbg] - %s\n", msg);
    printf("\x1b[0m");
  }
}
