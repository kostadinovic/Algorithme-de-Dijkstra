/* dijkstra.c
 * */

#include "dijkstra.h"


void print_distrow(int dststart[], int size) {
	for(int i = 0; i < size; i++)
		printf("+----------");
	printf("+\n");
	for(int i = 0; i < size; i++) {
		if(dststart[i] == INT_MAX)
			printf("|tbd       ");
		else
			printf("|%-10d", dststart[i]);
	}
	printf("|");
}

void print_disthead(Graph *p_graph, int size) {
	printf("Distance of node from start at each step\n");
	for(int i = 0; i < size; i++)
		printf("+----------");
	printf("+\n");
	for(int i = 0; i < size; i++)
		printf("|Node %-5d", (*((p_graph->pp_nd)+i))->name);
	printf("|\n");
}

Node **build_path(Edge *shortest_path[], Node *p_srcnd, Node *p_dstnd, int ndidmap[], int node_count) { // this is quite inefficiant as the path build contains the same informations as the edge array, but it is easier for processing data
	Node *p_node = p_dstnd;
	Edge *p_edge;
	Node **path = (Node **)malloc(node_count*sizeof(Node *));
	int i=0;
	*path = NULL; // this it the guardian value
	while(p_node->id != p_srcnd->id) {
		i++;
		*(path+i) = p_node;
		int curidx;
		for(int i=0; i < node_count; i++) {
			if(ndidmap[i] == p_node->id) {
				curidx = i;
				break;
			}
				
		}
		p_edge = shortest_path[ndidmap[curidx]];
		p_node = p_edge->src;
	}
	i++;
	*(path+i) = p_srcnd;
	path = realloc(path, (i+1)*sizeof(Node *));
	
	return path+i; // you have to read path in reverse order up to NULL
}

int print_path(Node **path) {
	if(!path || *path == NULL) {
		printf("Invalid path\n");
		return -1;
	}
	// the first node of the path is the latest in the array, consequently the array must be iterated over backward until NULL element (the guardian value)
	while(*(path-1)) {
		printf("%d->", (*path)->name);
		path--;
	}
	printf("%d", (*path)->name);

	return 0;
}

Node **dijkstra(Graph *p_graph, Node *p_srcnd, Node *p_dstnd, int f_prtDist) {
	int node_count = (p_graph->nd_cnt);
	int ndidmap[node_count]; // nodes IDs in order of pp_nd
	int visited[node_count]; // keep track of the nodes which have been traversed 
	int dststart[node_count]; // dststart[i] is the distance of (graph->nodes)+i from *p_srcnd
	Edge *shortest_path[node_count]; // the edge used by the shortest path to associated node
	
	// initialization of all arrays
	for(int i=0; i<node_count; i++) {
		ndidmap[i] = (*((p_graph->pp_nd)+i))->id;
		if(p_srcnd->id == ndidmap[i])
			dststart[i] = 0; // since node->id = position of node in graph->nodes
		else
			dststart[i] = INT_MAX;
		visited[i] = 0; // XXX: notice that if sortest_path[i] =! NULL visted[i] != 0
		shortest_path[i] = NULL;
	}

	if(f_prtDist) print_disthead(p_graph, node_count);
		
	Node *p_curnd = p_srcnd;
	for(int i=0; i<node_count; i++) {
		if(p_curnd == p_dstnd) {
			if(f_prtDist) { // used to print the distance array
				print_distrow(dststart, node_count);
				printf(" partial path : ");
				print_path(build_path(shortest_path, p_srcnd, p_curnd, ndidmap, node_count));
				printf("\n");
			}
			break;
		}

		int ndidx;
		for(int j=0; j<node_count; j++) // find the index of the array col associated with the node being checked
			if(p_curnd->id == ndidmap[j])
				ndidx = j;
			
		// visit all next nodes
		for(Edge **p_pe = p_curnd->pp_edg; p_pe < (p_curnd->pp_edg)+(p_curnd->edg_cnt); p_pe++) {
			Node *p_nxtnd = (*p_pe)->dst;
			int nxtidx;
			for(int j=0; j<node_count; j++) { 
				if(p_nxtnd->id == ndidmap[j]) {
					nxtidx = j;
					break;
				}
			}

			// update distance if it is shorter trough this path
			if(dststart[ndidx]+((*p_pe)->weight) < dststart[nxtidx]) {
				dststart[nxtidx] = dststart[ndidx]+((*p_pe)->weight);
				shortest_path[nxtidx] = *p_pe;
			}
		}

		// print the state of the distance array and the path being currenlty checked
		if(f_prtDist) {
			print_distrow(dststart, node_count);
			printf(" partial path : ");
			print_path(build_path(shortest_path, p_srcnd, p_curnd, ndidmap, node_count));
			printf("\n");
		}
		
		// mark current node as visited
		visited[ndidx] = 1;

		int min_dist = INT_MAX;
	
		// get the node with the shortest distance from start that has not already been visited
		p_curnd = NULL;
		for(int i=0; i < node_count; i++) {
			if(dststart[i] < min_dist && !visited[i]) {
				min_dist = dststart[i];
				p_curnd = *((p_graph->pp_nd)+i);
			}
		}

		if(p_curnd == NULL)
			break;
	}
	// print last line of the distance array
	if(f_prtDist) {
		for(int i = 0; i < (p_graph->nd_cnt); i++)
			printf("+----------");
		printf("+\n");
	}

	if(!p_curnd) { // case where no path can be found leading to destination
		return NULL;
	}
	
	Node **path = build_path(shortest_path, p_srcnd, p_dstnd, ndidmap, node_count); 

	return path;
}
