#include "definitions.h"

namespace 
{
const int INF = 1000000000;

struct edge_s{
    int a, b, c, flow; // a->b, c-capacity, flow=0
    edge_s(int a, int b, int c, int flow) : a(a), b(b), c(c), flow(flow) {}
};

vector< pair<int, int> > top_degree;
vector< pair<int, int> > top_flow;
vector<int> dis;
vector<int> ptr;
vector<edge_s> edgelist;
vector< vector<int> > edges_dup;
}

bool bfs_dinic(int s, int t) {
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    
    while (!q.empty() && dis[t] == -1) {
        int v = q.front();
        q.pop();
        
        for (int ind : edges_dup[v]) {
            int next = edgelist[ind].b;
            
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

long long dinic_flow(int s, int t) {
    long long flow = 0;
     
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
    
    dis.resize(2 * V, 0);
    ptr.resize(2 * V, 0);
    edges_dup.resize(2 * V, vector<int>(0));
    const int top = min(100, V);

    for (int i = 0; i < V; i++)
        top_flow.push_back(make_pair(0, i));

    for (int i = 0; i < V; i++) {
        top_degree.push_back(make_pair(edge[i].size(), i));
        for (int j = 0; j < edge[i].size(); j++) {
            int to = edge[i][j];
            dinic_addedge(i, to + V, V);
        }
        dinic_addedge(i + V, i, 1);
    }
    
    stable_sort(top_degree.rbegin(), top_degree.rend());
    
    cout << "Minimum cut between characters:" << endl;
    for (int i = 0; i < top; i++) {
        for (int j = i + 1; j < top; j++) {
            vector<int>::iterator p = find(edge[top_degree[i].second].begin(), edge[top_degree[i].second].end(), top_degree[j].second);
            
            if (p != edge[top_degree[i].second].end())
                continue;
            
            int flow = dinic_flow(top_degree[i].second, top_degree[j].second + V);
            cout << name[top_degree[i].second] << " -> " << name[top_degree[j].second] << " = " << flow << endl;     

            for (int k = 0; k < edgelist.size(); k++) {
                if ((edgelist[k].a == (edgelist[k].b + V)) && (edgelist[k].flow == 1)) {
                    top_flow[edgelist[k].b].first++;
                }
                edgelist[k].flow = 0;
            }
        }
    }
    
    stable_sort(top_flow.rbegin(), top_flow.rend());

    cout << endl << "Top involved characters in the flows:" << endl;
    for (int i = 0; i < top; i++) {
        cout << name[top_flow[i].second] << " (" << top_flow[i].first << ")" << endl;
    }
}
