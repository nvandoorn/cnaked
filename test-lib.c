#include "test-lib.h"
#include <stdio.h>

static const char *GREEN = "\033[0;32m";
static const char *RED = "\033[0;31m";
static const char *WHITE = "\033[1;37m";
static const char *ESCAPE = "\e[0m";

static void printPass() { printf("%s\tPassed\t\n%s", GREEN, ESCAPE); }

static void printFail(char *msg) {
  printf("%s\tFailed\t\n\t%s\n%s", RED, msg, ESCAPE);
}

int syncTest(char *testName, char *errMsg, int (*testCallback)()) {
  printf("Running %s...\n", testName);
  int r = testCallback();
  if (r) {
    printFail(errMsg);
  } else {
    printPass();
  }
  return r;
}

int asyncTest(char *testName, asyncTestHandler_t callback) {
  printf("Running %s\n", testName);
  callback(printPass, printFail);
}
