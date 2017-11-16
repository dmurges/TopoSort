/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * David Murges
 * 657384
 *
 * This module provides all the topological sorting functionality.
 *
*/
#ifndef TOPOSORT_H
#define TOPOSORT_H

#include "graph.h"

/* Returns a list of topologically sorted vertices using the DFS method */
extern List dfs_sort(Graph graph);

/*visit the nodes of the graph push node into new_list if it reaches leaf*/
extern int visit1(List* vertices,bool temporary[],bool permanent[],int numsorted,Vertex vertex);

/*setting false as default value of items in array*/
extern void populatearrays(bool* permanent,bool* temporary,Graph graph);

/*setting items in array to false*/
extern void initializearray(bool *alreadyVisited,Graph graph);

/* Returns a list of topologically sorted vertices using the Kahn method */
extern List kahn_sort(Graph graph);

/* Uses graph to verify vertices are topologically sorted */
extern bool verify(Graph graph, List list);

#endif
