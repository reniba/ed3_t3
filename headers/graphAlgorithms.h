#ifndef __GRAPH_ALGORITHMS__
#define __GRAPH_ALGORITHMS__

#include "graphRoutines.h"
#include "headerRoutines.h"
#include "messages.h"
#include "speciesRoutines.h"
#include <bits/stdc++.h>

typedef std::map<std::string, int> AUX_INDEX_MAP;
AUX_INDEX_MAP setIndexMap(GRAPH *graph);
void dfs(GRAPH *graph, AUX_INDEX_MAP *IndexMap);
int find_number_of_cycles(GRAPH *graph);
int minPopulation(GRAPH *graph, std::string src, std::string dest);
int isPath(GRAPH *graph, std::string src, std::string dest);
bool kosaraju(GRAPH *graph);
int kosaraju_number(GRAPH *graph);
#endif
