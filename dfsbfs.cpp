#include "definitions.h"

namespace
{
vector<bool> useddfs, usedbfs;
vector<int> comp;
}

void dfs(int u) {
    useddfs[u] = true;
    comp.push_back(u);
    for (int i : edge[u])
        if (!useddfs[i])
            dfs(i);
}

void bfs(int u, vector<int> &distance, vector<int> &path) {
    queue<int> q;
    q.push(u);
    usedbfs[u] = true;
    path[u] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int to : edge[u]) {
            if (!usedbfs[to]) {
                usedbfs[to] = true;
                q.push(to);
                distance[to] = distance[u] + 1;
                path[to] = u;
            }
        }
    }
}

void count_components() {
    freopen("components.txt", "w", stdout); // output file

    int comp_num = 0;
    useddfs.resize(V, false);
    for (int i = 0; i < V; i++) {
        if (!useddfs[i]) {
            comp.clear();
            dfs(i);
            comp_num++;
        }
    }
    cout << comp_num;
}

void calculate_diameter() {
    freopen("diameter.txt", "w", stdout); // output file

    int diameter = 0;
    int current_max = 0;
    double average_max = 0;
    double average_average = 0;
    vector< vector<int> > distribution(V, vector<int> (0));
    vector< vector<int> > max_path;
    vector<int> farthest_node;
    for (int i = 0; i < V; i++) {
        vector<int> distance_to(V, 0);
        vector<int> path(V,-1);
        usedbfs.clear();
        usedbfs.resize(V, false);
        bfs(i, distance_to, path);
        current_max = 0;
        for (int j = 0; j < V; j++) {
            average_average += distance_to[j];

            if (distance_to[j] > current_max)
                current_max = distance_to[j];

            if (distance_to[j] > diameter) {
                diameter = distance_to[j];
                farthest_node.clear();
                max_path.clear();
                max_path.push_back(path);
                farthest_node.push_back(j);
            } else if (distance_to[j] == diameter){
                max_path.push_back(path);
                farthest_node.push_back(j);
            }
        }
        average_max += current_max;
        distribution[current_max].push_back(i);
    }
    average_max /= V;
    average_average /= V*V;

    cout << "Diameter: " << diameter << endl;
    cout << "Average path: " << average_average << endl;
    cout << "Average farthest path: " << average_max << endl;

    vector < vector<int> > farthest_path;

    for (int i = 0; i < farthest_node.size(); i++) {
        farthest_path.push_back(vector<int>());
        for (int u = farthest_node[i]; u != -1; u = max_path[i][u])
            farthest_path[i].push_back(u);
    }

    cout << "Farthest paths:" << endl;
    for (int i = 0; i < farthest_path.size(); i++) {
        cout << i+1 << ": ";
        for (vector<int>::iterator j = farthest_path[i].begin(); j != farthest_path[i].end(); j++)
            cout << name[*j] << ". ";
        cout << endl;
    }

    int minimum = V;
    cout << "Farthest paths distribution:" << endl;
    for (int i = 0; i <= diameter; i++) {
        if (distribution[i].size() != 0 && i < minimum)
            minimum = i;

        cout << i << ": " << distribution[i].size() << endl;
    }

    cout << "Characters with minimum farthest path:" << endl;
    for (vector<int>::iterator i = distribution[minimum].begin(); i != distribution[minimum].end(); i++) {
        cout << name[*i] << endl;
    }
}
