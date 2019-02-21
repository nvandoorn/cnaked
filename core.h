#ifndef CNAKE_CORE_H
#define CNAKE_CORE_H

#include "game-state.h"

/**
 * Convert enum GameMove_t into something
 * you could send as a response
 */
int gameMoveToJson(enum GameMove_t *res, char *buff, int buffSize);

/**
 * Remake struct GameState_t with a one move
 * difference (described by one of enum GameMove_t).
 * This ensures 2 things:
 *  1) We always make copies of this state to avoid mutation
 *  2) It only ever differs by one move, to ensure we create
 *     a coherent graph.
 */
int remakeGameState(struct GameState_t *oldState, struct GameState_t *newState,
                    enum GameMove_t *move);

int core_setup(int argc, char *argv[]);

#endif
