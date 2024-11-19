#ifndef __GRAPH_ROUTINES__
#define __GRAPH_ROUTINES__

#include "headerRoutines.h"
#include "messages.h"
#include "speciesRoutines.h"
#include <bits/stdc++.h>

/*
 * represents the edge of the graph, contains the information of the destination node(hunt name) and
 * the weight of the node (population)
 */

typedef struct
{
    std::string food;
    int population;
} FOOD_NODE;

/*
 * represents a node of the graph, contains the source node information(hunter information)
 */
typedef struct
{
    std::string name;
    std::string species;
    std::string habitat;
    std::string diet;
    std::string type;
    int entry_degree, exit_degree, degree;
} NAME_NODE;
/*
 * Represents the graph
 * It is a pair vector, where each pair stores the node referring to a predator and its adjacency
 * list. It was chosen to use the pair to maintain a connection logic when ordering the vector
 */
typedef std::vector<std::pair<NAME_NODE, std::vector<FOOD_NODE>>> GRAPH;

// funtion declarations
NAME_NODE createNameNode(Dinosaur temp_dino);
FOOD_NODE createFoodNode(Dinosaur temp_dino);
void addGraph(GRAPH *graph, Dinosaur temp_dino);
void sortGraph(GRAPH *graph);
void printNode(GRAPH *temp_graph, int i, int j);
void printGraph(GRAPH *graph);
void initializeGraph(GRAPH *graph, char Dinosaur_file[]);

#endif
