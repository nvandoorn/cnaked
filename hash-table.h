#ifndef CNAKE_HASH_TABLE_H
#define CNAKE_HASH_TABLE_H

#include <pthread.h>

#define DUPLICATE_KEY_ERR -1
#define KEY_DOES_NOT_EXIST -2
#define FREE_EMPTY_NODE -3

#define HASH_TABLE_SIZE 4096 * 1024

struct hash_Node_t {
  int key;
  void *next;
  void *prev;
};

struct hash_Table_t {
  // lock the hash table
  // to ensure it's thread safe
  pthread_mutex_t lock;
  struct hash_Node_t *nodes[HASH_TABLE_SIZE];
  int nNodes;
};

int hash_init(struct hash_Table_t *t);

/**
 * Insert an integer value into a hash table
 *
 * This routine does modify the struct but uses
 * a mutex to maintain thread safety
 */
int hash_insert(struct hash_Table_t *t, int key);

/**
 * Remove an integer value
 *
 * Also threadsafe
 */
int hash_remove(struct hash_Table_t *t, int key);

/**
 * Check if the table contains a value
 *
 * _Should_ be safe from thread related problems
 * here since it's strictly a read
 */
int hash_contains(struct hash_Table_t *t, int key);

#endif
