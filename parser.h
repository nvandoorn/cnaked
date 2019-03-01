#ifndef CNAKE_PARSER_H
#define CNAKE_PARSER_H

#include "game-state.h"

#define JSON_PARSE_FAIL -1
#define EXPECTED_ARRAY -2
#define INSUFFICIENT_MEM -3

int parser_stringToState(char *reqBody, struct GameState_t *state);

void parser_stateToString(struct GameState_t *state);

#endif
