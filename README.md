# TopoSort

A topological sort of a directed graph is a linear odering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. For instance, the vertices of the graph may represent tasks to be performed, and the edges may represent constraints that one task must be performed before another; in this application, a topological ordering is just a valid sequence for the tasks.

The canonical application of topological sorting is in scheduling a sequence of jobs or tasks based on their dependencies

I use 2 algorithms in this program, the Kahn algorithm and the depth first search algorithm.

This program uses simple strings to assign dependencies and tasks.

I have included some test examples for you in the test folder.

# Compile
Open the terminal and change to the TopoSort directory.

use the "make" command to compile the program
The files given as input have to be in the given sequence:

First row the number of nodes, then the listing of the nodes.
After the nodes, the dependencies are listed, first the number of the node in the list, then a space and the number of the node that is dependent on the first.



# Print a directed graph
On the linux shell run ./toposort -p mygraph.dot mygraph.dot


# Toposort algorithms
For the DFS algorithm use the command:

./toposort -m 1 mygraph.txt > mygraph_toposort1.txt
It will give you a sequence of the nodes in topological order


For the kahn algorithm use:
./toposort -m 2 mygraph.txt > mygraph_toposort2.txt
It will also give you the node numbers in topological order

It will display the number of vertices and edges and will display the cpu time it took to run the sort.


# Verify

To verify that the nodes are actually in topological order run:

./toposort -v mygraph.txt < mygraph_toposort2.txt



To visualize the .dot files that display the graphs, download and open with graphviz.


