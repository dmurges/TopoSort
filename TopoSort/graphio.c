/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * David Murges
 * 657384
 *
 * This module provides all the IO functionality related to graphs.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graphio.h"

#define MAX_LINE_LEN 256


/* Loads the graph from input */
Graph load_graph(char *input) {
    /*assign the value of order to integer order*/
    int order = ordervalue(input);

    /*allocating memory for the graph and each vertex*/
    Graph graph = (Graph)malloc(sizeof(struct graph_t));
    graph->vertices = (Vertex)malloc(order*sizeof(struct vertex_t));
    graph->size = 0;
    assert(graph);

    /*allocating memory for each label*/
    for (int i = 0; i < order; ++i)
    {
        graph->vertices[i].in = NULL;
        graph->vertices[i].out = NULL;
        graph->vertices[i].label = (char*)malloc(MAX_LINE_LEN*sizeof(char));
    }

    /*create a file pointer and get rid of the order number*/
    FILE* fp;
    fp = fopen(input,"r");
    char label1[MAX_LINE_LEN];
    fgets(label1,MAX_LINE_LEN,fp);
    
    /*assigning the labels to vertices and get rid of \n*/
    for (int j = 0; j < order; j++)
    {
        fgets(graph->vertices[j].label,MAX_LINE_LEN,fp);
        strtok(graph->vertices[j].label,"\n");
        /*assign id */
        graph->vertices[j].id = j;
    }
    /*assign the graph size*/
    graph->size = graphsize(fp,graph);
    /*assign graph->order*/
    graph->order = order;

    
    return graph;
}



/* Prints the graph */
void print_graph(char *output, Graph graph) {

    /*create file pointer and write to file*/
    FILE* fp;
    fp = fopen(output,"w");
    /*print digraph { to file*/
    fprintf(fp,"digraph { \n");
    
    /*looping through every single node in vertices array*/
    int i=0;
    while (i < graph->order){

        /*if node has no outgoing edges print label*/
        if (graph->vertices[i].out==NULL)
        {
            fprintf(fp,"%s\n",graph->vertices[i].label);
        }

        /*if node has outgoing edges, print an arrow and all
        outgoing nodes inside brackets*/
        if (graph->vertices[i].out!=NULL)
        {

        fprintf(fp,"%s -> { ",graph->vertices[i].label);
        print_list(print_vertex_label,fp,graph->vertices[i].out);
        fprintf(fp,"} \n");

        }

        i++;

    }
    /*print the closing bracket*/
    fprintf(fp," }\n");

}


/*get the order value from text file turn it into an
integer and return the value*/
int ordervalue(char *input){
    char order[10];
    int val;
    FILE* fp;
    fp = fopen(input,"r");

    fgets(order,10,fp);
    val = atoi(order);
    return val;
}

/*returns the value of the graph size*/
int graphsize(FILE* fp,Graph graph){
    /*initialize in and outgoing edge*/
    int edgefrom=0;
    int edgeto=0;

    /*value of graph->size*/
    int value = 0;
    char removeline[MAX_LINE_LEN];

    /*taking the first edge, assign it to edgefrom and edgeto
    ,checks whether node points to itself and pushes them into the graph*/

    fscanf(fp,"%d %d",&edgefrom,&edgeto);
    if (edgefrom != edgeto)
    {
    prepend(&graph->vertices[edgeto].in,&((Vertex)graph->vertices)[edgefrom]);
    prepend(&graph->vertices[edgefrom].out,&((Vertex)graph->vertices)[edgeto]);
    value++;
    }

    
    
    /*read all edges until the end of the file and 
    push edges to the graph as long as node doesn't point to itself*/
    while (fgets(removeline,MAX_LINE_LEN,fp)!=NULL){

        fscanf(fp,"%d %d",&edgefrom,&edgeto);
        if (edgefrom!=edgeto)
        {
        prepend(&graph->vertices[edgeto].in,
            &((Vertex)graph->vertices)[edgefrom]);
        prepend(&graph->vertices[edgefrom].out,
            &((Vertex)graph->vertices)[edgeto]);

        /*increment size fo graph*/
        value++;
        }
        

    }
    /*in case no edges exist*/
    if (value!=-1)
    {
        value--;
    }

    return value;

}



/* Prints the destination vertex label surrounded by spaces */
void print_vertex_label(FILE *file, void *vertex) {
    if (vertex)         
    {
        fprintf(file, "%s ",((Vertex)vertex)->label);
    }
}

/* Prints the id of a vertex then a newline */
void print_vertex_id(FILE *file, void *vertex) {
    if (vertex)
        fprintf(file, "%d\n", ((Vertex)vertex)->id);
}

/* Returns a sequence of vertices read from file */
List load_vertex_sequence(FILE *file, Graph graph) {
    const char *err_duplicate = "Error: duplicate vertex %d %s\n";
    const char *err_order = "Error: graph order %d, loaded %d vertices\n";
    List list = NULL;
    int id;

    while(fscanf(file, "%d\n", &id) == 1) {
        assert(id >= 0);
        assert(id < graph->order);

        if (!insert_if(id_eq, graph->vertices + id, &list)) {
            fprintf(stderr, err_duplicate, id, graph->vertices[id].label);
            exit(EXIT_FAILURE);
        }
    }

    if (len(list) != graph->order) {
        fprintf(stderr, err_order, graph->order, len(list));
        exit(EXIT_FAILURE);
    }

    return list;
}
