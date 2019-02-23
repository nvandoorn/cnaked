#include "cjson/cJSON.h"
#include "game-state.h"
#include "parser.h"

int parseYou(cJSON *you, struct GameState_t *state) {
  int i = 0;
  cJSON *health, *body, *coord, *x, *y;
  health = cJSON_GetObjectItemCaseSensitive(you, "health");
  body = cJSON_GetObjectItemCaseSensitive(you, "body");
  state->ourHealth = health->valueint;
  cJSON_ArrayForEach(coord, body) {
    x = cJSON_GetObjectItemCaseSensitive(coord, "x");
    y = cJSON_GetObjectItemCaseSensitive(coord, "y");
    state->ourBody[i][0] = x->valueint;
    state->ourBody[i++][1] = y->valueint;
  };
}

int parser_stringToState(char *reqBody, struct GameState_t *state) {
  cJSON *reqMonitor = cJSON_parse(reqBody);
  cJSON *you;
  if (reqMonitor == NULL) {
    return JSON_PARSE_FAIL;
  }
  you = cJSON_GetObjectItemCaseSensitive(reqMonitor, "you");
  parseYou(you, state);
}
