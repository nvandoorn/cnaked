#include "core.h"
#include "game-state.h"
#include "graph.test.h"
#include "hash-table.test.h"
#include "test-lib.h"
#include <string.h>

int testMoveToJson() {
  enum GameMove_t move = UP;
  char buff[1024];
  int buffSize = 1024;
  int res = gameMoveToJson(&move, buff, buffSize);
  return strcmp(buff, "{\"move\":\"up\"}");
}

int main() {
  // core tests written here
  syncTest("gameMoveToJson", "JSON payload is incorrect", testMoveToJson);

  // Tests included from other lib
  // graph.test.c
  graph_test();
  // hash-table.test.c
  hash_test();
}
