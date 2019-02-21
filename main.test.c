#include "game-state.h"
#include "main.h"
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
  syncTest("gameMoveToJson", "JSON payload is incorrect", testMoveToJson);
}
