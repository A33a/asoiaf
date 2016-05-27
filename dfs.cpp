#include "definitions.h"

vector<bool> used;
int timer = 0;
vector<int> tin, fout;
vector < pair<int,int> > bridges;

void dfs(int v, int prev = -1) {
    used[v] = true;
    tin[v] = fout[v] = timer++;

    for (int i = 0; i < edge[v].size(); i++) {
        int to = edge[v][i];

        if (to == prev)  continue;

        if (used[to])
            fout[v] = min(fout[v], tin[to]);
        else {
            dfs(to, v);
            fout[v] = min(fout[v], fout[to]);

            if (fout[to] > tin[v])
                bridges.push_back(make_pair(v, to));
        }
    }
}

void find_bridges() {
    freopen("bridges.txt", "w", stdout); // output file

    used.resize(V, false);
    tin.resize(V);
    fout.resize(V);

    for (int i = 0; i < V; i++)
        if (!used[i])
            dfs(i);

    for (int i = 0; i < bridges.size(); i++) {
        cout << name[bridges[i].first] << " - " << name[bridges[i].second] << endl;
    }
}