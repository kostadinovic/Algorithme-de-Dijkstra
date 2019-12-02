/* graph.h
 * */

#ifndef _GRAPH_CORE_H_
#define _GRAPH_CORE_H_

#include <stdio.h>
#include <stdlib.h>


struct _edge;

typedef struct _node {
	int id;
	int edg_cnt;
	struct _edge **pp_edg; //pointer to array of struct _edge
	int name;
} Node;

typedef struct _edge {
	//src is kinda useless since the starting node is always the node containing the structure but 
	struct _node *src; //pointer to struct _node
	struct _node *dst; //pointer to struct _node
	int weight;
} Edge;

typedef struct _graph {
	int nd_cnt;
	struct _node **pp_nd; //pointer to array of struct _node
} Graph;

Node *create_node(int ndname);

Edge *create_edge(Node *p_srcnd, Node *p_dstnd, int weight);

Graph *create_graph(void);

Node **add_node(Graph *p_graph, Node *p_node);

Edge **add_edge(Node *p_node, Edge *p_edge);

Node *find_node_by_name(Graph *graph, int rname);

void add_to_graph(Graph *p_graph, const char *filepath);

void add_edge_to_graph_node_with_name(Graph *graph, Edge* edge, int rname);


#endif

