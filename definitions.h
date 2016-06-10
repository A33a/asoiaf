#ifndef DEF_H
#define DEF_H
#define _CRT_SECURE_NO_DEPRECATE
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <set>
#include <iterator>
#include <functional>

using namespace std;

extern vector<int> id;
extern vector< vector<int> > weight, edge;
extern map<int, string> name;
extern int V, E;

void read_data();
#endif
