#ifndef CNAKE_PARSER_H
#define CNAKE_PARSER_H

#include "game-state.h"

int parser_stringToState(char *reqBody, struct GameState_t *state);

#endif
