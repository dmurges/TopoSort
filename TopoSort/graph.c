/*David Murges
 *657384
*/
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

 #define MAX_LINE_LEN 256

/* Returns a pointer to a new graph with order vertices */
Graph new_graph(int order) {
    return NULL;
}

/* Returns whether aim and vertex are pointing to the same location */
bool ptr_eq(void *aim, void *vertex) {
    return false;
}

/* Returns whether aim and vertex have the same id */
bool id_eq(void *aim, void *vertex) {

	/*typecast aim and vertex and compare id*/
	if (((Vertex)aim)->id == ((Vertex)vertex)->id)
	{
		return true;
	}

    return false;
}

/* Add the edge from v1 to v2 to graph */
void add_edge(Graph graph, int v1, int v2) {
	
}

/* Free the memory allocated to graph */
void free_graph(Graph graph) {
	
}
