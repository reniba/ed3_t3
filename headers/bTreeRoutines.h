#ifndef __BTREE_ROUTINES__
#define __BTREE_ROUTINES__

#include "bTreeHeaderRoutines.h"
#include "funcoes_fornecidas.h"
#include "headerRoutines.h"
#include "speciesRoutines.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISK_PAGE_LEN 1600
#define REGISTER_LEN 160

#define BTREE_DISK_PAGE_LEN 93
#define ORDER 5

#define NOT_FOUND -1
#define FOUND 1

#define NULL_NODE -1
#define NULL_KEY -1
#define NULL_RRN -1

#define PROMOTION 1
#define NO_PROMOTION 0
#define ERROR -1

typedef struct
{
    long key;
    long RRN;
} KEY;

typedef struct page
{
    char leaf;
    int NumIndexedKeys;
    int RRNnode;
    KEY keys[ORDER - 1];
    int children[ORDER];
} PAGE;

typedef struct working_page
{
    char leaf;
    int NumIndexedKeys;
    int RRNnode;
    KEY keys[ORDER];
    int children[ORDER + 1];
} WORKING_PAGE;

// int searchDinoIndexBtree(Dinosaur *Dino, bTree_Header *btree_head, FILE *bTreePointer);
// int insertDinoIndexBtree(Dinosaur *Dino, FILE *bTreeFilename, bTree_Header *btree_head);
void printCurrentPage(PAGE temp_page);
PAGE inititializePage(bTree_Header *btree_head);
int insertKeyintoNode(PAGE *temp_page, KEY P_B_KEY, int P_B_RRN, int POS);
int writeBtreeIndexPage(PAGE *temp_page, int RRN, FILE *bTreePointer);
int readBtreeIndexPage(PAGE *temp_page, int RRN, FILE *bTreePointer);
int search(int RRN, long KEY, int *FOUND_RRN, int *FOUND_POS, FILE *bTreePointer);
long searchRRN(int RRN, long KEY, FILE *bTreePointer);
int insert(int CURRENT_RRN, KEY FUNCTION_KEY, int *PROMO_R_CHILD, KEY *PROMO_KEY,
           FILE *bTreePointer, bTree_Header *btree_head);

#endif
