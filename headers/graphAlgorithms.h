#ifndef __GRAPH_ALGORITHMS__
#define __GRAPH_ALGORITHMS__

#include "graphRoutines.h"
#include "messages.h"
#include "speciesRoutines.h"
#include <bits/stdc++.h>
//#include <cstdlib>
//#include <initializer_list>
//#include <iostream>
//#include <map>
//#include <vector>
//#include "bTreeHeaderRoutines.h"
//#include "funcoes_fornecidas.h"
#include "headerRoutines.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

// futuro: array_item
//  vector_item
/*typedef struct
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
} ARRAY_NODE;*/

// typedef std::pair<std::vector<ARRAY_NODE>, std::vector<std::vector<VECTOR_NODE>>> GRAPH;
// typedef std::vector<std::pair<ARRAY_NODE, std::vector<VECTOR_NODE>>> GRAPH;

// typedef std::vector<std::vector<GRAPH_NODE>> GRAPH;

typedef std::map<std::string, int> AUX_INDEX_MAP;
/*ARRAY_NODE createArrayNode(Dinosaur temp_dino);
VECTOR_NODE createVectorNode(Dinosaur temp_dino);
void addGraph(GRAPH *graph, Dinosaur temp_dino);
void sortGraph(GRAPH *graph);
void printNode(GRAPH *temp_graph, int i, int j);
void printGraph(GRAPH *graph);
void initializeGraph(GRAPH *graph, char Dinosaur_file[]);*/
AUX_INDEX_MAP setIndexMap(GRAPH *graph);
void dfs(GRAPH *graph, AUX_INDEX_MAP *IndexMap);
int dfs_number_of_cycles(GRAPH *graph, AUX_INDEX_MAP *IndexMap);
void initializeTranposedGraph(GRAPH *graph, GRAPH *transposedGraph, AUX_INDEX_MAP *indexMap);
int StrongCompsGraph(GRAPH *graph, AUX_INDEX_MAP *index_map);
int isStronglyConnected(GRAPH *graph, AUX_INDEX_MAP *index_map);
int minPopulation(GRAPH *graph, std::string src, std::string dest, AUX_INDEX_MAP *index_map);
int isPath(GRAPH *graph, AUX_INDEX_MAP *index_map, std::string src, std::string dest);
// int searchDinoIndexBtree(Dinosaur *Dino, bTree_Header *btree_head, FILE *bTreePointer);
// int insertDinoIndexBtree(Dinosaur *Dino, FILE *bTreeFilename, bTree_Header *btree_head);

/*void printCurrentPage(PAGE temp_page);
PAGE inititializePage(bTree_Header *btree_head);
int insertKeyintoNode(PAGE *temp_page, KEY P_B_KEY, int P_B_RRN, int POS);
int writeBtreeIndexPage(PAGE *temp_page, int RRN, FILE *bTreePointer);
int readBtreeIndexPage(PAGE *temp_page, int RRN, FILE *bTreePointer);
int search(int RRN, long KEY, int *FOUND_RRN, int *FOUND_POS, FILE *bTreePointer);
long searchRRN(int RRN, long KEY, FILE *bTreePointer);
int insert(int CURRENT_RRN, KEY FUNCTION_KEY, int *PROMO_R_CHILD, KEY *PROMO_KEY,
           FILE *bTreePointer, bTree_Header *btree_head);
*/
#endif
