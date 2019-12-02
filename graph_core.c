/* graph.c
 * */

#include "graph_core.h"


// id is not initilized in this function, because it only has meaning in the context of a graph so we'll let add_node set the nodes id
Node *create_node(int ndname) {
	Node *p_node = (Node *)malloc(sizeof(Node));
	if(!p_node) {
		printf("Could not create node\n");
		return NULL;
	}
	p_node->name = ndname;
	p_node->edg_cnt = 0;
	p_node->pp_edg = NULL;
	return p_node;
}

Edge *create_edge(Node *p_srcnd, Node *p_dstnd, int weight) {
	if(!p_srcnd || !p_dstnd) {
		printf("One of the node is invalid\n");
		return NULL;
	}

	Edge *p_edge = (Edge *)malloc(sizeof(Edge));	
	if(!p_edge) {
		printf("Could not create edge\n");
		return NULL;
	}
	p_edge->src = p_srcnd;
	p_edge->dst = p_dstnd;
	p_edge->weight = weight;
	return p_edge;
}

Graph *create_graph(void) {
	Graph *p_graph = (Graph *)malloc(sizeof(Graph));
	if(!p_graph) {
		printf("Could not create graph\n");
		return NULL;
	}
	p_graph->nd_cnt = 0;
	p_graph->pp_nd = NULL;

	return p_graph;
}

Node **add_node(Graph *p_graph, Node* p_node) {
	if(!p_graph) {
		printf("Graph does not exist\n");
		return NULL;
	}
	if(!p_node) {
		printf("Node does not exist\n");
		return NULL;
	}

	Node **pp_nwnd = (Node **)realloc(p_graph->pp_nd, ((p_graph->nd_cnt)+1)*sizeof(Node *)); // this is possible only because NULL is assigned to p_graph->p_nodes on creation
	if(!pp_nwnd) {
		printf("Could not resize p_graph->p_nodes\n");
		return NULL;
	}
	p_graph->pp_nd = pp_nwnd;

	Node **p_addnd = ((p_graph->pp_nd)+(p_graph->nd_cnt)); 
	*p_addnd = p_node;
	(*p_addnd)->id = (p_graph->nd_cnt)++; // TODO: find a better id

	return p_graph->pp_nd;
}

Edge **add_edge(Node *p_node, Edge* p_edge) {
	if(!p_node) {
		printf("Node does not exist\n");
		return NULL;
	}
	if(!p_edge) {
		printf("Edge does not exist\n");
		return NULL;
	}

	Edge **pp_nwedg = (Edge **)realloc(p_node->pp_edg, ((p_node->edg_cnt)+1)*sizeof(Edge *));
	if(!pp_nwedg) {
		printf("Could not resize p_node->p_edges\n");
		return NULL;
	}
	
	p_node->pp_edg = pp_nwedg;
	*( (p_node->pp_edg)+(p_node->edg_cnt) ) = p_edge;
	(p_node->edg_cnt)++;

	return p_node->pp_edg;
}

// this function returns only the first node in graph->nodes which name matches rname
Node *find_node_by_name(Graph *p_graph, int ndname) {
	for(Node **p_pn = p_graph->pp_nd; p_pn < (p_graph->pp_nd)+(p_graph->nd_cnt); p_pn++) {
		Node *p_n = *p_pn;
		if(p_n->name == ndname) {
			return p_n;
		}
	}
	
	return NULL; // no match has been found
}

#include "graph_misc.h"

void add_to_graph(Graph *p_graph, const char *filepath) {
	FILE *p_f;
	int srcname, dstname, weight;
	p_f = fopen(filepath, "r");
	int ret;

	if(!p_f) {
		printf("File not found\n");
		exit(1);
	}
	// pretty sure ret is useless
	// this is not the most efficient way to do it
	// a better way would be to look for all edges originating node a putting them in an array and using add_edges 
	while( (ret = fscanf(p_f, "%d %d %d", &srcname, &dstname, &weight))!=EOF && ret!=0 ) {
		
		Node *p_srcnd;
		Node *p_dstnd;
		
		if( !(p_srcnd = find_node_by_name(p_graph, srcname)) ) {
			p_srcnd = create_node(srcname);
			add_node(p_graph, p_srcnd);
		}
		
		if( !(p_dstnd = find_node_by_name(p_graph, dstname)) ) {
			p_dstnd = create_node(dstname);
			add_node(p_graph, p_dstnd);
		}

		Edge *p_edg = create_edge(p_srcnd, p_dstnd, weight);
		add_edge( find_node_by_name(p_graph, srcname), p_edg );
	}
	fclose(p_f);
}

