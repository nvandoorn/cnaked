#include "game-state.h"
#include "parser.h"
#include "parser.test.h"
#include "test-lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static const char *SAMPLE_BODY_PATH = "./sample-body.json";

#define PARSER_TIME_LIMIT_MS 0.3

// TODO fix dangling file descriptor
// leading to weird read conditions
int parserSuccess() {
  FILE *f;
  size_t readRes;
  char buff[1024];
  struct GameState_t state;
  int r;
  f = fopen(SAMPLE_BODY_PATH, "r");
  if (f == NULL)
    return -1;
  readRes = fread(buff, 1, 1024, f);
  if (readRes <= 0)
    return -1;
  r = parser_stringToState(buff, &state);
  parser_printState(&state);
  // test the properties that don't require iteration for now
  if (r)
    return r;
  if (state.turn != 4)
    goto fail;
  if (state.ourHealth != 90)
    goto fail;
  if (state.nSnakes != 1)
    goto fail;

  fclose(f);
  return 0;
fail:
  fclose(f);
  return -1;
}

int parserSucessPerformance() {
  double cpuTime;
  clock_t start, end;
  start = clock();
  parserSuccess();
  end = clock();
  cpuTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  return cpuTime >= PARSER_TIME_LIMIT_MS;
}

int parser_test() {
  char msgBuff[1024];
  syncTest("parser_stringToState", "Success path failed", parserSuccess);
  snprintf(msgBuff, 1024, "Parser took over %f ms", PARSER_TIME_LIMIT_MS);
  syncTest("parser_stringToState perf", msgBuff, parserSucessPerformance);
}
