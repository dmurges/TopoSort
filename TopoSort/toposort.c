/* David Murges
 * 657384
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "toposort.h"


/* Returns a list of topologically sorted vertices using the DFS method */

List dfs_sort(Graph graph) {

	/*create a new list*/
	List new_list = NULL;
	
	/*create boolean arrays and set values equal to false*/
	bool temporary[graph->order];
	bool permanent[graph->order];

	/*counting the number of sorted nodes*/
	int numsorted = 0;

	/*populate array with false values*/
	populatearrays(permanent,temporary,graph);

	/*count number of nodes visited*/
	int i=0;
	/*looping through array of nodes*/
	while(numsorted!=graph->order && i<graph->order){
	
		/*calling the visit function*/
		visit1(&new_list,temporary,permanent,numsorted,&graph->vertices[i]);
		i++;
		
	}

	/*return the topologically sorted list*/
    return new_list;
}

/*visit the nodes of the graph push node into new_list if it reaches leaf*/
int visit1(List* vertices,bool temporary[],bool permanent[],
           int numsorted,Vertex vertex){

	/*check whether the node has already been visited*/
	if (temporary[vertex->id]==true)
	{
		/*if that's the case print an error message and exit*/
		fprintf(stderr, "NOT A DAG\n");
		exit(EXIT_FAILURE);
	
	}

	/*gets executed if the node ahs not been visited yet*/
	if (temporary[vertex->id] == false && permanent[vertex->id]==false)
	{
		/*mark n temporarily*/
		temporary[vertex->id]=true;

		/*checking whether there exists an edge between m and n*/
		for (List m=vertex->out;m!=NULL;m=m->next)
		{
			/*recursive function visiting every node that has an edge to n*/
			visit1(vertices,temporary,permanent,numsorted,((Vertex)m->data));
		}

		/*mark n permanently and unmark n temporarily*/
		temporary[vertex->id]=false;
		permanent[vertex->id]=true;
		/*push n to head of the new list */
		prepend(vertices,((Vertex)vertex));
		numsorted++;
	}

	return numsorted;
}


/*setting false as default value of items in array*/
void populatearrays(bool* permanent,bool* temporary,Graph graph){
	for (int i = 0; i < graph->order; i++)
	{
		temporary[i]=false;
		permanent[i]=false;
	}
}


/* Returns a list of topologically sorted vertices using the Kahn method */
List kahn_sort(Graph graph) {

	/*create 2 new lists one that will contain the sorted elements
	the other is a set of nodes with no incoming edges*/
	List new_list = NULL;
	List S = NULL;

	/*this integer will decrease everytime an edge is deleted*/
	int edgenum = graph->size;
	
	/*checking if nodes with no incoming edges exist already*/
	for (int i = 0; i < graph->order; ++i)
	{
		if (len(graph->vertices[i].in)==0)
		{
			insert(&((Vertex)graph->vertices)[i],&S);			
		}
	}
	/*temporarily placeholder for popped vertex*/
	Vertex T;

	while(S!=NULL){
		/*remove node from S*/
		T=pop(&S);

		/*add n to tail of the new list*/
		insert(T,&new_list);

		/*looping through all nodes that have an edge from n to m*/
		for (List m=T->out;m!=NULL;m=m->next)
		{

			/*delete the incoming edge*/
			del(id_eq, T,&((Vertex)(m->data))->in);
			/*decrement edgenum*/
			edgenum--;

			/*if the node has no incoming edges we insert it into the new list*/
			if (len(((Vertex)m->data)->in)==0)
			{
				insert(((Vertex)m->data),&S);
			}
		}

	}

	/*If the graph has edges, it has at least one cycle 
	checking by the decrement of edgenum with each edge
	removal*/
	if (edgenum!=-1)
	{
		fprintf(stderr, "ERRRORR\n");
		exit(EXIT_FAILURE);
	}

	/*return topologically sorted list*/
    return new_list;
}


/* Uses graph to verify vertices are topologically sorted */
bool verify(Graph graph, List vertices) {
	/*create a new list*/
	List Visited = NULL;
	/*boolean array that sets already visited nodes to true*/
	bool alreadyVisited[graph->order];

	/*setting items in array to false*/
	initializearray(alreadyVisited,graph);
	
	/*for each vertex n in List L*/
	for (List n=vertices;n!=NULL;n=n->next)
	{
		/*add n to Visited list and set index of id equal to true*/
		insert(((Vertex)n->data),&Visited);
		alreadyVisited[((Vertex)n->data)->id]=true;

		/*for each vertex m reachable from n*/
		for (List m=((Vertex)n->data)->out; m!=NULL; m=m->next)
		{	
			/*if m has already been added to Visited*/
			if (alreadyVisited[((Vertex)m->data)->id]==true)
				{
					/*the topological ordering is invalid*/
					return false;
				}
		}
	}

	return true;
}

/*setting items in array to false*/
void initializearray(bool *alreadyVisited,Graph graph){
	for (int i = 0; i < graph->order; ++i)
	{
		alreadyVisited[i]=false;
	}
}

