#include "definitions.h"

const int INF = 1000000000;

struct edge_s{
    int a, b, c, flow; // a->b, c-capacity, flow=0
    edge_s(int a, int b, int c, int flow) : a(a), b(b), c(c), flow(flow) {}
};

vector< pair<int, int> > top_degree;
vector<int> dis;
vector<int> ptr;
vector<edge_s> edgelist;
vector< vector<int> > edges_dup;

bool bfs_dinic(int s, int t) {
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    
    while (!q.empty() && dis[t] == -1) {
        int v = q.front();
        q.pop();
        
        for (int i = 0; i < edges_dup[v].size(); i++) {
            int ind = edges_dup[v][i],
            next = edgelist[ind].b;
            
            if (dis[next] == -1 && edgelist[ind].flow < edgelist[ind].c) {
                q.push(next);
                dis[next] = dis[v] + 1;
            }
        }
    }
    
    return dis[t] != -1;
}

int dfs_dinic(int v, int t, int flow) {
    if (!flow) {
        return 0;
    }
    
    if (v == t) {
        return flow;
    }
    
    for (; ptr[v] < (int) edges_dup[v].size(); ptr[v]++) {
        int ind = edges_dup[v][ptr[v]];
        int next = edgelist[ind].b;
        
        if (dis[next] != dis[v] + 1) {
            continue;
        }
        
        int pushed = dfs_dinic(next, t, min(flow, edgelist[ind].c - edgelist[ind].flow));
        
        if (pushed) {
            edgelist[ind].flow += pushed;
            edgelist[ind ^ 1].flow -= pushed;
            return pushed;
        }
    }
    
    return 0;
}

long long dinic_flow(int n, int s, int t) {
    long long flow = 0;
    
    dis.resize(V, 0);
    ptr.resize(V, 0);
    edges_dup.resize(V, vector<int>());
    
    while (true) {
        fill(dis.begin(), dis.end(), -1);
        
        if (!bfs_dinic(s, t)) {
            break;
        }
        
        fill(ptr.begin(), ptr.end(), 0);
        
        while (int pushed = dfs_dinic(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

void dinic_addedge(int a, int b, int c) {
    edges_dup[a].push_back((int) edgelist.size());
    edgelist.push_back(edge_s(a, b, c, 0));
    edges_dup[b].push_back((int) edgelist.size());
    edgelist.push_back(edge_s(b, a, 0, 0));
}

void find_cut() {
    freopen("cut_min.txt", "w", stdout); // output file
    
    for (int i = 0; i < V; i++) {
        top_degree.push_back(make_pair(edge[i].size(), i));
        for (int j = 0; j < edge[i].size(); j++) {
            int to = edge[i][j];
            dinic_addedge(i, to + V, V);
        }
        dinic_addedge(i + V, i, 1);
    }
    
    stable_sort(top_degree.rbegin(), top_degree.rend());
    
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            vector<int>::iterator p = find(edge[top_degree[i].second].begin(), edge[top_degree[i].second].end(), top_degree[j].second);
            
            if (p == edge[top_degree[i].second].end()) {
                continue;
            } else {
                cout << name[top_degree[i].second] << " -> " << name[top_degree[j].second] << endl;
            }
            
        }
    }
    cout << "lala";
}
