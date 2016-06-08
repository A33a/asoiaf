#ifndef CUT_H
#define CUT_H

struct edge_s{
    int a, b, c, flow;
    edge_s(int a, int b, int c, int flow);
};

bool bfs_dinic(int s, int t);
int dfs_dinic(int v, int t, int flow);
long long dinic_flow(int s, int t);
void dinic_addedge(int a, int b, int c);
void find_cut();

#endif
