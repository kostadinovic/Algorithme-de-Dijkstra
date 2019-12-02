CC = gcc
CFLAGS = -Wall -O2
EXEC = dijkstra

HEADERS = graph.c

all: dijkstra

dijkstra: dijkstra_main.o graph_core.o graph_misc.o dijkstra.o
	$(CC) -o $(EXEC) dijkstra_main.o graph_core.o graph_misc.o dijkstra.o $(CFLAGS)

dijkstra_main.o: dijkstra_main.c graph_misc.h graph_core.h dijkstra.h
	$(CC) -o dijkstra_main.o -c dijkstra_main.c $(CFLAGS)

graph_core.o: graph_core.c graph_core.h
	$(CC) -o graph_core.o -c graph_core.c $(CFLAGS)

graph_misc.o: graph_misc.c graph_core.h graph_misc.h
	$(CC) -o graph_misc.o -c graph_misc.c $(CFLAGS)

dijkstra.o: dijkstra.c dijkstra.h graph_core.h graph_misc.h
	$(CC) -o dijkstra.o -c dijkstra.c $(CFLAGS)

clean:
	rm -rf *.o 

mrproper: clean
	rm -fr $(EXEC)
