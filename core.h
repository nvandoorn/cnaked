#ifndef CNAKE_CORE_H
#define CNAKE_CORE_H

#include "game-state.h"
int gameMoveToJson(enum GameMove_t *res, char *buff, int buffSize);
int core_setup(int argc, char *argv[]);

#endif
