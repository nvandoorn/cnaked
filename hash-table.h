#ifndef CNAKE_HASH_TABLE_H
#define CNAKE_HASH_TABLE_H

#include <pthread.h>

#define DUPLICATE_KEY_ERR -1

struct hash_Table_t {
  // lock the hash table
  // to ensure it's thread safe
  pthread_mutex_t lock;
};

int hash_init(struct hash_Table_t *t);

int hash_insert(struct hash_Table_t *t, int key);

int hash_remove(struct hash_Table_t *t, int key);

int hash_contains(struct hash_Table_t *t, int key);

#endif
