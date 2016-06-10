#include "definitions.h"

vector<int> p;

int dsu_get(int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

void dsu_unite(int u, int v) {
    u = dsu_get(u);
    v = dsu_get(v);

    if (rand() & 1)
        swap(u, v);

    if (u != v)
        p[u] = v;
}


void get_spanning_tree() {
    freopen("spanning.txt", "w", stdout); // output file

    vector < pair < int, pair<int, int> > > edges_weights, result;

    vector < vector<bool> > used;
    for (int i = 0; i < V; i++) {
        used.push_back(vector<bool>(V, false));
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < edge[i].size(); j++) {
            int cur_v = edge[i][j];
            if (!used[i][cur_v]) {
                edges_weights.push_back(make_pair(weight[i][j], make_pair(i, cur_v)));
                used[i][cur_v] = true;
                used[cur_v][i] = true;
            }
        }
    }

    sort(edges_weights.begin(), edges_weights.end(), greater< pair < int, pair<int, int> > >());

    for (int i = 0; i < V; i++) {
        p.push_back(i);
    }

    for (int i = 0; i < E; i++) {
        int u = edges_weights[i].second.first;
        int v = edges_weights[i].second.second;
        int w = edges_weights[i].first;
        (void)w;

        if (dsu_get(u) != dsu_get(v)) {
            result.push_back(edges_weights[i]);
            dsu_unite(u, v);
        }
    }

    for (vector < pair < int, pair<int, int> > >::iterator i = result.begin(); i != result.end(); i++) {
        cout << id[(i->second).first] << " " << id[(i->second).second] << " " << i->first << endl;
    }
}
