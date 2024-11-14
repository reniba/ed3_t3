#ifndef __GRAPH_ROUTINES__
#define __GRAPH_ROUTINES__

#include "headerRoutines.h"
#include "messages.h"
#include "speciesRoutines.h"
#include <bits/stdc++.h>

typedef struct
{
    std::string name;
    std::string food;
    int population;
} VECTOR_NODE;

typedef struct
{
    std::string name;
    std::string species;
    std::string habitat;
    std::string diet;
    std::string type;
    int entry_degree, exit_degree, degree;
} ARRAY_NODE;

typedef std::vector<std::pair<ARRAY_NODE, std::vector<VECTOR_NODE>>> GRAPH;

ARRAY_NODE createArrayNode(Dinosaur temp_dino);
VECTOR_NODE createVectorNode(Dinosaur temp_dino);
void addGraph(GRAPH *graph, Dinosaur temp_dino);
void sortGraph(GRAPH *graph);
void printNode(GRAPH *temp_graph, int i, int j);
void printGraph(GRAPH *graph);
void initializeGraph(GRAPH *graph, char Dinosaur_file[]);

#endif
