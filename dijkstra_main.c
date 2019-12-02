/* main.c
 * */

#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "graph_misc.h"
#include "graph_core.h"
#include "dijkstra.h"


void clean_stdin(void) {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

void print_gandalf(void) {
	FILE *gandalf;
	if( !(gandalf =fopen(".gandalf.txt", "r")) )
		printf("The way is shut. It was made by those who are Dead, and the Dead keep it, until the time comes. The way is shut\n(no path has been found\n");
	else {
		char c;
		while( (c=fgetc(gandalf)) != EOF ) {
			printf("%c", c);
		}
		fclose(gandalf);
	}
}

Node *select_node(Graph *p_graph, const char *node_type) {
	int r, ndName = -1;
	Node *p_node = NULL;

	do {
		printf("%s : ", node_type);
		r = scanf("%d", &ndName);
		clean_stdin();
		if ( !(p_node = find_node_by_name(p_graph, ndName)) )
			printf("Invalid node, please enter a valid node mame\n");
	} while( !(p_node) || !r );

	return p_node;
}

int main(int argc, char **argv) {
	// check for presence of graph file
	if(argc < 2) {
		printf("Usage : %s graph_file\n", argv[0]);
		return -1;
	}

	int opt;
	int f_prtDist = 0;
	int gandalf = 0;
	char *mode = (char *)malloc(20*sizeof(char));
	strcpy(mode, "pair");
	char *output_file = (char *)malloc(20*sizeof(char));
	char *graph_file = (char *)malloc(20*sizeof(char));

	while( (opt = getopt(argc, argv, "m:po:g")) != -1 ) {
		switch(opt) {
			case 'm': // determine shortest path between all nodes
				strcpy(mode, optarg);
				break;
			case 'p': // print distance array at each step
				f_prtDist = 1;
				break;
			case 'o': // output result to file
				strcpy(output_file, optarg);
				break;
			case 'g':
				gandalf = 1;
				break;
			case ':':
				printf("need value\n");
				break;
			case '?':
				printf("unknown option\n");
				break;
		}
	}

	strcpy(graph_file, argv[optind]); // graph file is the last and only mandatory argument

	Graph *g = create_graph();
	add_to_graph(g, graph_file);

	printf("Nodes of the graph :\n");
	print_graph_nodes(g);
	printf("\n");

	if(strcmp(mode, "matrix") == 0) { // matrix mode
		for(Node **pp_n1 = g->pp_nd; pp_n1 < (g->pp_nd)+(g->nd_cnt); pp_n1++) {
			printf("Paths from %d :\n", (*pp_n1)->name);
			for(Node **pp_n2 = g->pp_nd; pp_n2 < (g->pp_nd)+(g->nd_cnt); pp_n2++) {
				Node **path;
				if( !(path = dijkstra(g, *pp_n1, *pp_n2, f_prtDist)) )
					printf("no path has been found from %d to %d \n", (*pp_n1)->name, (*pp_n2)->name);
				else {
					printf("shortest path from %d to %d : ", (*pp_n1)->name, (*pp_n2)->name);
					print_path(path);
					printf("\n");
				}
			}
			printf("\n");
		}	
	}

	else if(strcmp(mode, "source") == 0) {
		int r;
		Node *p_srcnd = NULL;
	
		printf("Choose your nodes from the list above\n");
		
		p_srcnd = select_node(g, "Start node");
		printf("\n");

		printf("Paths from %d :\n", p_srcnd->name);
		for(Node **pp_n = g->pp_nd; pp_n < (g->pp_nd)+(g->nd_cnt); pp_n++) {
			Node **path;
			if( !(path = dijkstra(g, p_srcnd, *pp_n, f_prtDist)) )
				printf("no path has been found from %d to %d \n", p_srcnd->name, (*pp_n)->name);
			else {
				printf("shortest from %d to %d : ", p_srcnd->name, (*pp_n)->name);
				print_path(path);
				printf("\n");
			}
	
		}
	}

	else if(strcmp(mode, "pair") == 0) { // pair mode
		int r;
		Node *p_srcnd = NULL;
		Node *p_dstnd = NULL;
	
		printf("Choose your nodes from the list above\n");
		
		p_srcnd = select_node(g, "Start node");
		p_dstnd = select_node(g, "Destination");	
		printf("\n");
	
		Node **path;
		if( !(path = dijkstra(g, p_srcnd, p_dstnd, f_prtDist)) ) {
			if(gandalf)
				print_gandalf();
			else
				printf("no path has been found from %d to %d \n", p_srcnd->name, p_dstnd->name);
		}
		else {
			printf("shortest from %d to %d : ", p_srcnd->name, p_dstnd->name);
			print_path(path);
			printf("\n");
		}
		printf("\n");

	}
	
	else {
		printf("Option %s not recognized\n", mode);
		return -1;
	}

	return 0;
}

