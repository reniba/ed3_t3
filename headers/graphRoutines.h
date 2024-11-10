#ifndef __GRAPH_ROUTINES__
#define __GRAPH_ROUTINES__

#include "speciesRoutines.h"
#include <bits/stdc++.h>
#include <vector>

//#include "bTreeHeaderRoutines.h"
//#include "funcoes_fornecidas.h"
//#include "headerRoutines.h"
//#include "speciesRoutines.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

typedef struct
{
    char species[MAX_FIELD_LEN];
    char habitat[MAX_FIELD_LEN];
    char diet[MAX_FIELD_LEN];
    int entry_degree, exit_degree, degree;
} GRAPH_NODE;

typedef std::vector<std::vector<GRAPH_NODE>> GRAPH;

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
