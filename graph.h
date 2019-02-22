#ifndef CNAKE_GRAPH_H
#define CNAKE_GRAPH_H

#define EMPTY_NODE_ERR -1
#define NULL_GRAPH_DEREF -2
#define NODE_OUT_OF_MEM -3

struct graph_Node_t {
  int id;
  void *value; // point to anything and live on the edge
  int nArcs;
  int maxNArcs;
  struct graph_Node_t **arcs;
};

struct graph_Graph_t {
  int nNodes;
  struct graph_Node_t *root;
  struct graph_Node_t *currentNode;
};

typedef int (*graph_TraverseHandler_t)(struct graph_Node_t *node, void *ctx);

int graph_makeGraph(struct graph_Graph_t *g, struct graph_Node_t *root);

int graph_insertNode(struct graph_Graph_t *g, struct graph_Node_t *toInsert,
                     struct graph_Node_t *toConnect);

int graph_gotoRoot(struct graph_Graph_t *g);

int graph_traverse(struct graph_Graph_t *g, graph_TraverseHandler_t handler,
                   void *ctx);

#endif
