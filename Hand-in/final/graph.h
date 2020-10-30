#ifndef GRAPH_PY_H
#define GRAPH_PY_H
#include "GraphClass.h"

mtm::graph* create();

void destroy(mtm::graph* graph);

mtm::graph* addVertex(mtm::graph* graph, const char* v);
mtm::graph* addEdge(mtm::graph* graph, const char* v1, const char* v2);

void disp(mtm::graph* graph);

mtm::graph* graphUnion(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out);
mtm::graph* graphIntersection(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out);
mtm::graph* graphDifference(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out);
mtm::graph* graphProduct(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out);
mtm::graph* graphComplement(mtm::graph* graph_in, mtm::graph* graph_out);
#endif