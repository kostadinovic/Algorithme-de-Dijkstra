/* graph_misc.c
 * */

#include "graph_misc.h"

// this is basically just a helper function now and should be intergrated in print_node_edges
int print_edge(Edge *p_edge) {
	if(!p_edge) {
		printf("Edge does not exist or is invalid\n"); // this should theorically never happen as edges are checked for NULL before being added to node->edges in add_edge and add_edges
		return -1;
	}
	// edges are printed using the following format : source_node_id -( edge_weight )-> destination_node_id
	printf("%d-(%d)->%d\n", p_edge->src->name, p_edge->weight, p_edge->dst->name);

	return 0;
}

int print_node_edges(Node *p_node) {
	for(Edge **p_pe = p_node->pp_edg; p_pe < (p_node->pp_edg)+(p_node->edg_cnt); p_pe++) {
		print_edge(*p_pe);
	}

	return 0;
}

int print_graph_nodes(Graph *p_graph) {
	for(Node **p_pn = p_graph->pp_nd; p_pn < (p_graph->pp_nd)+(p_graph->nd_cnt); p_pn++) {
		printf("%d ", (*p_pn)->name);
	}
	printf("\n");

	return 0;
}

