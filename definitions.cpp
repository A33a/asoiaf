#include "definitions.h"

vector<int> id; // origin ID of characters
vector< vector<int> > weight; // weights of edges
vector< vector<int> > edge; // the graph's edges
map<int, string> name; // names of characters
int V, E; // amount of vertices and edges

void read_data() {
    freopen("input.in", "r", stdin); // read from the input file

    cin >> V >> E;
  
    id.resize(V);
    weight.resize(V);
    edge.resize(V);
    vector<int> reverseID(E);

    int u;
    char s[100];
    for (int i = 0; i < V; i++) { // read the names
        scanf("%d %[^\n]", &u, s);
        name[i] = string(s);
        id[i] = u; // origin ID by assigned ID
        reverseID[u] = i; // assigned ID by origin ID
    }

    int a, b, w;
    for (int i = 0; i < E; i++) { // read the edges and weights
        cin >> a >> b >> w;
        edge[reverseID[a]].push_back(reverseID[b]);
        edge[reverseID[b]].push_back(reverseID[a]);
        weight[reverseID[a]].push_back(w);
        weight[reverseID[b]].push_back(w);
    }
}
