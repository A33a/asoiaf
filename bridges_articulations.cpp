#include "definitions.h"

vector<bool> used, usedcnt;
int timer = 0;
vector<int> tin, fout, articulations;
vector < pair<int,int> > bridges;

int count_rec(int v, int skip) {
    int cnt = 1;
    usedcnt[v] = true;

    for (int i = 0; i < edge[v].size(); i++) {
        int to = edge[v][i];

        if(to == skip || usedcnt[to]) 
            continue;

        cnt += count_rec(to, skip);
    }
    
    return cnt;
}

int count_from(int v, int skip, bool clean = true){
    usedcnt.resize(V, false);

    if (clean) {
        for (int i = 0; i < usedcnt.size(); i++)
            usedcnt[i] = false;
    }
         
    return count_rec(v, skip);
}

void dfs(int v, int prev = -1) {
    used[v] = true;
    tin[v] = fout[v] = timer++;

    int root_calls = 0;
    bool in_ar_list = false;
    for (int i = 0; i < edge[v].size(); i++) {
        int to = edge[v][i];

        if (to == prev)  continue;

        if (used[to])
            fout[v] = min(fout[v], tin[to]);
        else {
            dfs(to, v);
            fout[v] = min(fout[v], fout[to]);

            if (fout[to] > tin[v]) {
                bridges.push_back(make_pair(v, to));
            }
            
            if (fout[to] >= tin[v] && prev != -1 && !in_ar_list) {
                articulations.push_back(v);
                in_ar_list = true;
            }
            
            root_calls++;
        }
    }
    
	if (prev == -1 && root_calls > 1)
		articulations.push_back(v);
}

void find_bridges_and_articulations() {
    freopen("bridges_and_articulations.txt", "w", stdout); // output file

    used.resize(V, false);
    tin.resize(V);
    fout.resize(V);

    for (int i = 0; i < V; i++)
        if (!used[i])
            dfs(i);
    
    cout << "Bridges:" << endl;
    for (int i = 0; i < bridges.size(); i++) {
        cout << name[bridges[i].first] << " (" << count_from(bridges[i].first, bridges[i].second) << ") - " << name[bridges[i].second] << " (" << count_from(bridges[i].second, bridges[i].first) <<")" << endl;
    }
    
    
    cout << endl << "Articulation points:" << endl;  
    for (int i = 0; i < articulations.size(); i++) {
        int cur = articulations[i];
        cout << name[cur];
        
        for (int i = 0; i < usedcnt.size(); i++)
            usedcnt[i] = false;
            
        for (int j = 0; j < edge[cur].size(); j++) {
            if (!usedcnt[edge[cur][j]]) {
                int comp_size = count_from(edge[cur][j], cur, false); 
                cout << " (" << comp_size << ")";
            }
        }
        cout << endl;
    }
}
