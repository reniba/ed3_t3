#ifndef __GRAPH_ROUTINES__
#define __GRAPH_ROUTINES__

#include "speciesRoutines.h"
//#include <bits/stdc++.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

//#include "bTreeHeaderRoutines.h"
//#include "funcoes_fornecidas.h"
#include "headerRoutines.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

// futuro: array_item
//  vector_item
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

// typedef std::pair<std::vector<ARRAY_NODE>, std::vector<std::vector<VECTOR_NODE>>> GRAPH;
typedef std::vector<std::pair<ARRAY_NODE, std::vector<VECTOR_NODE>>> GRAPH;

// typedef std::vector<std::vector<GRAPH_NODE>> GRAPH;

ARRAY_NODE createArrayNode(Dinosaur temp_dino);
VECTOR_NODE createVectorNode(Dinosaur temp_dino);
void addGraph(GRAPH *graph, Dinosaur temp_dino);
void sortGraph(GRAPH *graph);
void printNode(GRAPH *temp_graph, int i, int j);
void printGraph(GRAPH *graph);

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
