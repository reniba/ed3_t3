#ifndef __BTREE_HEADER_ROUTINES__
#define __BTREE_HEADER_ROUTINES__

#include <stdio.h>
#include <stdlib.h>

#define BTREE_DISK_PAGE_LEN 93

typedef struct
{
    char status;
    int rootNode;
    int nextNodeRRN;
} bTree_Header;

bTree_Header initializeBtreeHeader();
void print_bTreeHeader(bTree_Header btree_head);
int bTree_readHeader(bTree_Header *head, FILE *file);
int bTree_writeHeader(bTree_Header *head, FILE *file);
int bTree_updateHeader(bTree_Header *head, FILE *file);

#endif
