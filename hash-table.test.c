#include "hash-table.h"
#include "hash-table.test.h"
#include "test-lib.h"
#include <pthread.h>
#include <stdio.h>

int hashInit() {
  struct hash_Table_t t;
  int r;
  r = hash_init(&t);
  if (r)
    return r;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    if (t.nodes[i] != NULL)
      return -1;
  }
  // grab a lock to make sure the
  // mutex is valid
  return pthread_mutex_lock(&t.lock);
}

int hashInsert() {
  struct hash_Table_t t;
  int r;
  r = hash_init(&t);
  if (r)
    return r;
  r = hash_insert(&t, 42);
  return r;
}

int hashRemove() {
  struct hash_Table_t t;
  int r, big;
  big = 100000;
  r = hash_init(&t);
  if (r)
    return r;
  for (int i = 0; i < big; i++) {
    r = hash_insert(&t, i);
    if (r)
      return r;
  }
  for (int i = 0; i < big; i++) {
    r = hash_remove(&t, i);
    if (r) {
      return r;
    }
  }
  return t.nNodes != 0;
}

int hashContains() {
  struct hash_Table_t t;
  int r;
  r = hash_init(&t);
  if (r)
    return r;
  r = hash_insert(&t, 42);
  if (r)
    return r;
  r = hash_contains(&t, 42);
  return r != 1;
}

int hashContainsNotFound() {
  struct hash_Table_t t;
  int r, big;
  big = 10000;
  r = hash_init(&t);
  if (r)
    return r;
  for (int i = 0; i < big; i++) {
    r = hash_insert(&t, i);
    if (r)
      return r;
  }
  r = hash_contains(&t, big + 1);
  return r;
}

int hashContainsBigFound() {
  struct hash_Table_t t;
  int r, big;
  big = 10000;
  r = hash_init(&t);
  if (r)
    return r;
  for (int i = 0; i < big; i++) {
    r = hash_insert(&t, i);
    if (r)
      return r;
  }
  r = hash_contains(&t, big / 2);
  return r != 1;
}

void *hashInsertThreaded_handler(void *ctx) {
  struct hash_Table_t *t = ctx;
  for (int i = 0; i < 100000; i++) {
    hash_insert(t, 100000 + i);
  }
  return NULL;
}

int hashInsertThreaded() {
  pthread_t thread;
  struct hash_Table_t t;
  int r;
  r = pthread_create(&thread, NULL, hashInsertThreaded_handler, &t);
  if (r)
    return r;

  r = hash_init(&t);
  if (r)
    return r;
  for (int i = 0; i < 100000; i++) {
    r = hash_insert(&t, i);
    if (r)
      return r;
  }
  return pthread_join(thread, NULL);
}

int hashInsertDupe() {
  struct hash_Table_t t;
  int r;
  r = hash_init(&t);
  if (r)
    return r;
  r = hash_insert(&t, 42);
  if (r)
    return r;
  r = hash_insert(&t, 42);
  return r != DUPLICATE_KEY_ERR;
}

void *hailMary_handler(void *ctx) {
  struct hash_Table_t *t = ctx;
  int r;
  for (int i = 0; i < 100000; i++) {
    r = hash_insert(t, i);
  }
}

int hailMary() {
  pthread_t thread;
  struct hash_Table_t t;
  int r;

  r = hash_init(&t);
  if (r)
    return r;
  r = pthread_create(&thread, NULL, hailMary_handler, &t);
  if (r)
    return r;
  r = pthread_join(thread, NULL);
  printf("%d\n", t.nNodes);
  if (r)
    return r;
  for (int i = 0; i < 100000; i++) {
    r = hash_remove(&t, i);
    if (r)
      return r;
  }
}

int hash_test() {
  syncTest("hash_init", "Hash init success path failed", hashInit);
  syncTest("hash_insert", "Hash insert success path failed", hashInsert);
  syncTest("hash_remove", "Hash remove success path failed", hashRemove);
  syncTest("hash_contains", "Hash contains success path failed", hashContains);
  syncTest("hash_contains big", "Hash contains \"big\" success path failed",
           hashContainsBigFound);
  syncTest("hash_contains not found", "Hash contains not found failed",
           hashContainsNotFound);
  // syncTest("hash_insert multithread", "Hash insert multithread failed",
  //          hashInsertThreaded);
  syncTest("hash_insert dupe", "Hash insert did not return correct error",
           hashInsertDupe);
  syncTest("Hail Mary", "Not shocking", hailMary);
}
