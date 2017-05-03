# Graph theory in A Game of Thrones
Statistics of "A Song Of Ice And Fire" based on graph theory. The graph of characters' connections is extracted from 5 first books using machine learning by [Erik Germani](http://atseajournal.com/asoiaf/). The graph algorithms are implemented in C++.
## Algorithms used in analysis
### BFS
The breadth-first search algorithm is used to calculate the diameter of the graph and farthest path for all vertices and the average of it. 
### DFS
The depth-first search algorithm is used to calculate the amount of connected components in the graph.
### Bron-Kerbosch algorithm
Used for calculating the maximal cliques in the graph.
### Kruskal's algorithm
Used for building the spanning tree of the graph. 
### Bridges & Articulation points
Used DFS with time and additional out function for determining bridges and articulation points
### Dinic's algorithm
Used Dinic's algorithm for calculating maximal flow of extended graph to determine cut vertices instead of edges. 
### How to build
Now it is possible to use CMake to generate a build config, for example:

```
$ mkdir build && cd build
$ cmake ..
$ make
```
