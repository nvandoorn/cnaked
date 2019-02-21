#ifndef TEST_LIB_H
#define TEST_LIB_H

typedef void (*asyncTestHandler_t)(void (*pass)(), void (*fail)(char *msg));

int syncTest(char *testName, char *errMsg, int (*testCallback)());
int asyncTest(char *testName, asyncTestHandler_t callback);

#endif
