/* dijkstra.h
 * */

#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "graph_core.h"
#include "graph_misc.h"


Node **dijkstra(Graph *graph, Node *start_node, Node *end_node, int print_dist);

int print_path(Node **path);


#endif
