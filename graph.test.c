#include "graph.h"
#include "graph.test.h"
#include "stdlib.h"
#include "test-lib.h"

int makeGraphNullDeref() {
  return graph_makeGraph(NULL, NULL) != NULL_GRAPH_DEREF;
}

int makeGraphEmptyNode() {
  struct graph_Graph_t g;
  struct graph_Node_t n = {.value = NULL};
  return graph_makeGraph(&g, &n) != EMPTY_NODE_ERR;
}

int makeGraphSuccess() {
  struct graph_Graph_t g;
  int val = 5;
  struct graph_Node_t n = {.value = &val, .maxNArcs = 1024};
  return graph_makeGraph(&g, &n) != 0;
}

int insertNodeNullDeref() {
  struct graph_Graph_t g;
  double val = 6;
  struct graph_Node_t *arcsN[1024];
  struct graph_Node_t n = {.value = &val, .maxNArcs = 1024, .arcs = arcsN};
  graph_makeGraph(&g, &n);
  return graph_insertNode(&g, &n, NULL) != NULL_GRAPH_DEREF;
}

int insertNodeEmptyNode() {
  struct graph_Graph_t g;
  double val = 7;
  struct graph_Node_t *arcsN[1024];
  struct graph_Node_t n = {.value = &val, .maxNArcs = 1024, .arcs = arcsN};
  struct graph_Node_t m = {.value = NULL};
  graph_makeGraph(&g, &n);
  return graph_insertNode(&g, &m, &n) != EMPTY_NODE_ERR;
}

int insertNodeOutOfMem() {
  struct graph_Graph_t g;
  double val = 8;
  struct graph_Node_t *arcsM[1024];
  struct graph_Node_t m = {.value = &val, .maxNArcs = 1024, .arcs = arcsM};
  struct graph_Node_t n = {
      .value = &val, .maxNArcs = 0, .arcs = NULL, .nArcs = 0};
  graph_makeGraph(&g, &n);
  return graph_insertNode(&g, &m, &n) != NODE_OUT_OF_MEM;
}

int insertNodeSuccess() {
  struct graph_Graph_t g;
  double val = 9;
  struct graph_Node_t *arcsN[1024], *arcsM[1024];
  struct graph_Node_t m = {
      .value = &val, .maxNArcs = 1024, .arcs = arcsM, .nArcs = 0};
  struct graph_Node_t n = {
      .value = &val, .maxNArcs = 1024, .arcs = arcsN, .nArcs = 0};
  graph_makeGraph(&g, &n);
  return graph_insertNode(&g, &m, &n) != 0;
}

int makeGraphTests() {
  syncTest("graph_makeGraph null deref", "Failed to return null deref err",
           makeGraphNullDeref);
  syncTest("graph_makeGraph empty node", "Failed to return empty node err",
           makeGraphEmptyNode);
  syncTest("graph_makeGraph success", "Happy path failed (shit's super fucked)",
           makeGraphSuccess);
  return 0;
}

int insertNodeTests() {
  syncTest("graph_insertNode null deref", "Failed to return null deref err",
           insertNodeNullDeref);
  syncTest("graph_insertNode empty node", "Failed to return empty node err",
           insertNodeEmptyNode);
  syncTest("graph_insertNode out of mem", "Failed to return out of mem err",
           insertNodeOutOfMem);
  syncTest("graph_insertNode success",
           "Happy path failed (shit's super fucked)", insertNodeSuccess);
  return 0;
}

int graph_test() {
  makeGraphTests();
  insertNodeTests();
  return 0;
}
