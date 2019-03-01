#ifndef GAME_STATE_H
#define GAME_STATE_H

#define COORD 2
#define MAX_SNAKE_LEN 1024
#define N_MAX_SNAKES 9
#define N_MAX_FOOD 100
#define MAX_ID_SIZE 512

/**
 * This structure represents one incoming request.
 * Note that this assumes all algorithms are stateless
 * (in the sense that they have no memory, or maybe it will?)
 * and do not modify this structure.
 *
 * This structure should always be populated
 * by a parser function that transforms string => struct GameState_t
 *
 * Note that we do not include ourself in the body array
 * or the nSkakes count
 */
struct GameState_t {
  int width;
  int height;

  int turn;
  int ourHealth;
  // Model our body as a 2d array
  int ourBody[COORD][MAX_SNAKE_LEN];
  int ourBodyLen;
  char ourId[MAX_ID_SIZE];

  // Note that we specifically opt
  // for a "struct of arrays" over
  // an "array of structs" to save a few
  // bytes. Does it matter? not sure yet

  // Read more here
  // https://stackoverflow.com/questions/8377667/layout-in-memory-of-a-struct-struct-of-arrays-and-array-of-structs-in-c-c
  int nSnakes;
  int nFood;
  int health[N_MAX_SNAKES];
  int body[COORD][MAX_SNAKE_LEN][N_MAX_SNAKES];
  int snakeLens[N_MAX_SNAKES];
  int food[COORD][N_MAX_FOOD];
};

enum GameMove_t { UP, DOWN, LEFT, RIGHT };

enum GameRank_t { AVOID = 0, ALIVE, FED, ALPHA_AF };

#endif
