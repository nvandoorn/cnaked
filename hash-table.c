#include "hash-table.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int computeHashIndex(int key) {
  int r = key % HASH_TABLE_SIZE;
  return r;
}

struct hash_Node_t *linearListSearch(struct hash_Node_t *node, int key) {
  while (node->next != NULL) {
    if (node->key == key)
      return node;
    node = (struct hash_Node_t *)node->next;
  }
  return NULL;
}

int hash_init(struct hash_Table_t *t) {
  // mark all node "slots" as NULL initially
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    t->nodes[i] = NULL;
  }
  t->nNodes = 0;
  return pthread_mutex_init(&t->lock, NULL);
}

// we don't _need_ a malloc because
// in theory we could predictably insert one stattically
// and then dynamically link all collisions, assuming
// the table is large enough
int hash_insert(struct hash_Table_t *t, int key) {
  int r, index;
  struct hash_Node_t *node, *slot;
  r = pthread_mutex_lock(&t->lock);
  if (r)
    return r;

  index = computeHashIndex(key);
  slot = t->nodes[index];

  if (slot != NULL && slot->key == key) {
    return DUPLICATE_KEY_ERR;
  }

  node = malloc(sizeof(struct hash_Node_t));
  node->key = key;
  node->next = NULL;
  node->prev = NULL;

  // easy case
  if (slot == NULL) {
    t->nodes[index] = node;
  } // harder-ish case
  else {
    while (slot->next != NULL) {
      slot = (struct hash_Node_t *)slot->next;
    }
    slot->next = node;
    node->prev = slot;
  }
  t->nNodes++;
  if (t->nNodes < 0) {
    printf("%d\n", t->nNodes);
  }
  r = pthread_mutex_unlock(&t->lock);
  return r;
}

// TODO free da node
int hash_remove(struct hash_Table_t *t, int key) {
  int r, hashKey;
  struct hash_Node_t *node;
  r = pthread_mutex_lock(&t->lock);
  if (r)
    return r;
  hashKey = computeHashIndex(key);
  node = t->nodes[hashKey];
  // could not find it case
  if (node == NULL) {
    return KEY_DOES_NOT_EXIST;
  }

  // Note that all error exits should
  // try and unlock it first
  // direct hit case
  else if (node->key == key) {
    // move up the next node
    if (node->next != NULL) {
      t->nodes[hashKey] = node->next;
      node->prev = NULL;
    }
    // empty it out case
    else {
      t->nodes[hashKey] = NULL;
    }
  }
  // linear probing case
  else {
    node = linearListSearch(node, key);
    if (node == NULL) {
      pthread_mutex_unlock(&t->lock);
      return KEY_DOES_NOT_EXIST;
    }
    if (node->next != NULL) {
      // we assume this node
      // must have a previous
      // since we had to search to find it
      struct hash_Node_t *newNext = node->next;
      struct hash_Node_t *newPrev = node->prev;
      newPrev->next = newNext;
      newNext->prev = newPrev;
    }
  }
  // This should never happen.
  // If we have nothing to free,
  // we should have exited from
  // an error before hitting this
  if (node == NULL) {
    pthread_mutex_unlock(&t->lock);
    return FREE_EMPTY_NODE;
  }
  free(node);
  t->nNodes--;
  r = pthread_mutex_unlock(&t->lock);
  return r;
}

int hash_contains(struct hash_Table_t *t, int key) {
  int r, hashKey, contains;
  r = pthread_mutex_lock(&t->lock);
  if (r)
    return r;

  hashKey = computeHashIndex(key);
  if (t->nodes[hashKey] == NULL) {
    contains = 0;
    goto done;
  } else {
    if (t->nodes[hashKey]->key == key) {
      contains = 1;
      goto done;
    } else {
      contains = linearListSearch(t->nodes[hashKey], key) != NULL;
      goto done;
    }
  }
done:
  r = pthread_mutex_unlock(&t->lock);
  if (r)
    return r;
  return contains;
}
