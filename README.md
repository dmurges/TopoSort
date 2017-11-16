# TopoSort

A topological sort of a directed graph is a linear odering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. For instance, the vertices of the graph may represent tasks to be performed, and the edges may represent constraints that one task must be performed before another; in this application, a topological ordering is just a valid sequence for the tasks.

The canonical application of topological sorting is in scheduling a sequence of jobs or tasks based on their dependencies

I use 2 algorithms in this program, the Kahn algorithm and the depth first search algorithm.

This program uses simple string to assign dependencies and tasks.

To 
