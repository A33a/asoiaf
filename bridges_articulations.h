#ifndef BRAR_H
#define BRAR_H

void dfs(int v, int p);
int count_rec(int v, int skip);
int count_from(int v, int skip, bool clean = true);
void find_bridges_and_articulations();

#endif
