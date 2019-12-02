# Disjkstra algorithm C implementation

## About : 

The Dijkstra algorithm, published by Edsger Dijkstra in 1959, is an algorithm used to determine the shortest path between two nodes of a graph.
In this implementation we will use it exclusively on non-euclidian graphs. 

## Getting started :

Clone the repository `git clone https://github.com/Balocre/dijkstra_c_project.git`, and run `make`.

## Usage : 

`./dijkstra [-m mode] [-p] file` where file is a specially formated graph file.

**Modes** :

 - `matrix` : output the shortest path between all nodes two by two
 - `source` : output the shortest path from one node to all the others
 - `pair`   : output the shortest path between two nodes
 

**Graph file** :

The graph file format is the following :

- Each represents a transition between 2 nodes and is constituted of 3 `int` separted by 1 space (e.g. 1 2 3).
- The first int represents the name of the first node, the second represents the name of the second node and the third is the weight of the transition.

Example :
```
1 2 1
1 3 2 
2 3 1
3 4 9
```
