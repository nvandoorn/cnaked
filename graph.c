#include "graph.h"
#include "thpool.h"
#include <pthread.h>
#include <stdlib.h>

int id = 0;

int graph_makeGraph(struct graph_Graph_t *g, struct graph_Node_t *root) {
  if (g == NULL || root == NULL)
    return NULL_GRAPH_DEREF;
  if (root->value == NULL)
    return EMPTY_NODE_ERR;
  g->root = root;
  g->currentNode = root;
  g->nNodes = 1;
  return 0;
}

int graph_insertNode(struct graph_Graph_t *g, struct graph_Node_t *toInsert,
                     struct graph_Node_t *toConnect) {
  if (g == NULL || toInsert == NULL || toConnect == NULL)
    return NULL_GRAPH_DEREF;
  if (toInsert->value == NULL)
    return EMPTY_NODE_ERR;
  if (toConnect->nArcs + 1 > toConnect->maxNArcs)
    return NODE_OUT_OF_MEM;

  toInsert->id = id++;

  (toConnect->nArcs)++;
  (toInsert->nArcs)++;
  toConnect->arcs[toConnect->nArcs] = toInsert;
  toInsert->arcs[toInsert->nArcs] = toConnect;
  (g->nNodes)++;
  return 0;
}

int graph_gotoRoot(struct graph_Graph_t *g) {
  if (g == NULL || g->currentNode == NULL || g->root == NULL)
    return NULL_GRAPH_DEREF;
  g->root = g->currentNode;
  return 0;
}

int graph_traverse(struct graph_Graph_t *g, graph_TraverseHandler_t handler,
                   void *ctx) {
  return 1;
}
