#ifndef GAME_STATE_H
#define GAME_STATE_H

#define COORD 2
#define MAX_SNAKE_LEN 1024
#define N_MAX_SNAKES 9

/**
 * This structure represents one incoming request.
 * Note that this assumes all algorithms are stateless
 * (in the sense that they have no memory, or maybe it will?)
 * and do not modify this structure.
 *
 * This structure should always be populated
 * by a parser function that transforms string => struct GameState_t
 */
struct GameState_t {
  // Model us
  char *gameId;
  int turn;
  int ourHealth;
  // Model our body as a 2d array
  int ourBody[COORD][MAX_SNAKE_LEN];

  // Note that we specifically opt
  // for a "struct of arrays" over
  // an "array of structs" to save a few
  // bytes. Does it matter? not sure yet

  // Read more here
  // https://stackoverflow.com/questions/8377667/layout-in-memory-of-a-struct-struct-of-arrays-and-array-of-structs-in-c-c
  int health[N_MAX_SNAKES];
  int body[COORD][MAX_SNAKE_LEN][N_MAX_SNAKES];
};

enum GameRank_t { AVOID = 0, ALIVE, FED, ALPHA_AF };

#endif
