#include "test-lib.h"
#include <stdio.h>

char *GREEN = "\033[0;32m";
char *RED = "\033[0;31m";
char *WHITE = "\033[1;37m";

void printPass() { printf("%s\tPassed\t\n", GREEN); }

void printFail(char *msg) { printf("%s\tFailed\t\n\t%s\n", RED, msg); }

int syncTest(char *testName, char *errMsg, int (*testCallback)()) {
  printf("Running %s...\n", testName);
  if (testCallback()) {
    printFail(errMsg);
  } else {
    printPass();
  }
}

int asyncTest(char *testName, asyncTestHandler_t callback) {
  printf("Running %s\n", testName);
  callback(printPass, printFail);
}
