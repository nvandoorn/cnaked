#include "game-state.h"
#include "json-parser/json.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

json_value *flatSearch(json_value *value, const char *name) {
  int n = value->u.object.length;
  for (int i = 0; i < n; i++) {
    if (!strcmp(name, value->u.object.values[i].name)) {
      return value->u.object.values[i].value;
    }
  }
  return NULL;
}

int parseBody(json_value *bodyArray, int storage[COORD][MAX_SNAKE_LEN],
              int *storageLen, int cellLen) {
  int n, m;
  json_value *coordSet, *coord;
  if (bodyArray->type != json_array) {
    printf("hello\n");
    return EXPECTED_ARRAY;
  }
  n = bodyArray->u.array.length;
  if (cellLen < COORD || *storageLen < n)
    return INSUFFICIENT_MEM;
  // iterate over each set of coordinates
  *storageLen = n;
  for (int i = 0; i < n; i++) {
    coordSet = bodyArray->u.array.values[i];
    m = coordSet->u.object.length;
    // iterate over the x,y pairs
    for (int j = 0; j < m; j++) {
      coord = coordSet->u.object.values[j].value;
      storage[i][j] = coord->u.integer;
    }
  }
  return 0;
}

int parseBoard(json_value *val, struct GameState_t *state) {
  json_value *iter;
  int len, r;
  len = N_MAX_FOOD;
  iter = flatSearch(val, "width");
  state->width = iter->u.integer;
  iter = flatSearch(val, "height");
  state->height = iter->u.integer;
  iter = flatSearch(val, "food");
  parseBody(val, state->food, &len, COORD);
  state->nFood = len;
done:
  return r;
}

int parseFood(json_value *val, struct GameState_t *state) { return -1; }

int parseAllSnakes(json_value *val, struct GameState_t *state) { return -1; }

int parseSnake(json_value *val, struct GameState_t *state) { return -1; }

int parseYou(json_value *val, struct GameState_t *state) {
  int r, length;
  json_value *body, *health, *id;
  length = MAX_SNAKE_LEN;
  health = flatSearch(val, "health");
  state->ourHealth = health->u.integer;
  body = flatSearch(val, "body");
  id = flatSearch(val, "id");
  strncpy(state->ourId, id->u.string.ptr, MAX_ID_SIZE);
  r = parseBody(body, state->ourBody, &length, COORD);
  state->ourBodyLen = length;
  if (r)
    goto done;
done:
  return r;
}

int parseTurn(json_value *val, struct GameState_t *state) {
  json_value *turn = flatSearch(val, "turn");
  state->turn = turn->u.integer;
}

int parseMainObject(json_value *value, struct GameState_t *state) {
  int r = -1;
  json_value *you, *board;
  if (value == NULL) {
    goto done;
  }
  parseTurn(value, state);
  you = flatSearch(value, "you");
  parseYou(you, state);
  board = flatSearch(value, "board");
  parseBoard(board, state);
done:
  return r;
}

/**
 * @public
 */
int parser_stringToState(char *reqBody, struct GameState_t *state) {
  json_value *reqValue = json_parse((json_char *)reqBody, strlen(reqBody));
  if (reqValue == NULL) {
    return JSON_PARSE_FAIL;
  }
  parseMainObject(reqValue, state);
  json_value_free(reqValue);
  return 0;
}

/**
 * @public
 */
void parser_printState(struct GameState_t *state) {
  int n;
  printf("Priting state @ %x\n", state);
  printf("turn: %d\n", state->turn);
  printf("ourHealth: %d\n", state->ourHealth);
  printf("ourId: %s\n", state->ourId);
  printf("nSnakes %d\n", state->nSnakes);
  printf("ourBodyLen: %d\n", state->ourBodyLen);
  printf("ourBody: \n");
  // iterate over each set of coords
  // for our body
  for (int i = 0; i < state->ourBodyLen; i++) {
    printf("\t x: %d, y: %d\n", state->ourBody[i][0], state->ourBody[i][1]);
  }
  printf("nSnakes: %d\n", state->nSnakes);
  // iterate over each snake
  for (int i = 0; i < state->nSnakes; i++) {
    printf("body[%d]: \n", i);
    // itereate over the set of coords in the body
    n = state->snakeLens[i];
    printf("\tsnakeLens[%d]: %d", i, n);
    printf("\thealth[%d]: %d", i, state->health[i]);
    for (int j = 0; j < n; j++) {
      printf("\t\tx: %d, y: %d\n", state->body[i][j][0], state->body[i][j][1]);
    }
  }
  printf("nFood: %d\n", state->nFood);
  for (int i = 0; i < state->nFood; i++) {
    printf("food[%d]: \n", i);
    printf("\tx: %d, y: %d\n", state->food[i][0], state->food[i][1]);
  }
}
