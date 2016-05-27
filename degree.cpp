#include "definitions.h"

void degree() {
    freopen("degree.txt", "w", stdout); // output file

    vector< pair<int,int> > degree(V);
    for (int i = 0; i < V; i++) {
        degree[i] = make_pair(edge[i].size(), i);
    }

    stable_sort(degree.begin(), degree.end());

    for (int i = V-1; i >= 0; i--) {
        cout << name[degree[i].second] << ": " << degree[i].first << endl;
    }
}

