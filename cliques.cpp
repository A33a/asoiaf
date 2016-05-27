#include "definitions.h"

vector < vector<int> > cliques;

bool compare_vectors_by_size(const vector<int> &i, const vector<int> &j)
{
    return (i.size() > j.size());
}

void bron_kerbosch(set <int> R, set <int> P, set <int> X) { // where R is probable clique, P - possible vertices in clique, X - exluded vertices
    if (P.size() == 0 && X.size() == 0) { // R is maximal clique
        cliques.push_back(vector<int>(0));
        for (set<int>::iterator i = R.begin(); i != R.end(); i++) {
            cliques.back().push_back(*i);
        }
    }
    else {
        set <int> foriterate = P;
        for (set<int>::iterator i = foriterate.begin(); i != foriterate.end(); i++) {
            set <int> newR;
            set <int> newP;
            set <int> newX;

            newR = R;
            newR.insert(*i);

            set_intersection(P.begin(), P.end(), edge[*i].begin(), edge[*i].end(), inserter(newP, newP.begin()));

            set_intersection(X.begin(), X.end(), edge[*i].begin(), edge[*i].end(), inserter(newX, newX.begin()));

            bron_kerbosch(newR, newP, newX);

            P.erase(*i);
            X.insert(*i);
        }
    }
}

void find_cliques() {
    freopen("cliques.txt", "w", stdout); // output file

    set <int> P;
    for (int i = 0; i < V; i++) {
        P.insert(i);
        stable_sort(edge[i].begin(), edge[i].end());
    }
    
    bron_kerbosch(set<int>(), P, set<int>());

    stable_sort(cliques.begin(), cliques.end(), compare_vectors_by_size);

    cout << "Distribution:" << endl;
    int max_size = 0;
    int max_counter = 0;
    for (int i = cliques.size()-1; i >= 0 ; i--) {
        if (cliques[i].size() > max_size) {
            if (max_counter > 0) {
                cout << max_size << ": " << max_counter << endl;
            }
            max_size = cliques[i].size();
            max_counter = 0;
        }

        max_counter++;
    }
    if (max_counter > 0) {
        cout << max_size << ": " << max_counter << endl;
    }

    cout << "Cliques:" << endl;
    for (int i = 0; i < cliques.size(); i++) {
        cout << i + 1 << "(" << cliques[i].size() << "): ";
        for (int j = 0; j < cliques[i].size(); j++) {
            cout << name[cliques[i][j]] << ". ";
        }
        cout << endl;
    }
}