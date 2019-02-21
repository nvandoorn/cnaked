#include <stdio.h>
#include <stdlib.h>

#include "core.h"
#include "game-state.h"
#include "parser.h"
#include "server.h"

#define DEFAULT_PORT 5000

void parseArgs(struct server_Ctx_t *ctx, int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: ./cnaked PORT\n");
    exit(1);
  }
  int port = atoi(argv[0]);
  ctx->port = port == 0 ? DEFAULT_PORT : port;
}

// TODO I have no idea how this function
// should pass back the move... but a pointer
// is starting to look kindof shitty
// (thinking about thread APIs mostly)
int traverse(struct GameState_t *state, enum GameMove_t *res) {}

int gameMoveToJson(enum GameMove_t *res, char *buff, int buffSize) {
  char *moveStr;
  // save a byte, pass a pointer
  switch ((*res)) {
  case UP:
    moveStr = "up";
    break;
  case DOWN:
    moveStr = "down";
    break;
  case LEFT:
    moveStr = "left";
    break;
  case RIGHT:
  default:
    moveStr = "right";
    break;
  }
  return snprintf(buff, buffSize, "{\"move\":\"%s\"}", moveStr);
}

void moveHandler(struct server_Req_t *req, struct server_Res_t *res,
                 void *ctx) {
  enum GameMove_t move;
  // Allocate space for the very first node
  struct GameState_t *state = malloc(sizeof(struct GameState_t));
  // Parse the raw request body string into
  // the struct
  int parseRes = parser_stringToState(req->body, state);
  // Recursively traverse from here.
  // Please see comment on traverse routine
  int traverseRes = traverse(state, &move);
  free(state);
}

int core_setup(int argc, char *argv[]) {
  struct server_Ctx_t ctx;
  parseArgs(&ctx, argc, argv);
  server_start(&ctx);
  server_attachRouteHandler("move", moveHandler, NULL);
  return 0;
}
