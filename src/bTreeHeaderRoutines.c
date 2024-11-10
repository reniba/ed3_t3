#include "./../headers/bTreeHeaderRoutines.h"

/* initializeBtreeHeader
 *
 * Creates a bTree header for a bTree index file with 0 pages written
 *
 */
bTree_Header initializeBtreeHeader()
{
    bTree_Header head;
    head.nextNodeRRN = 0;
    head.rootNode = -1;
    head.status = '0';
    return head;
}

/* print_bTreeHeader
 *
 * Print the 3 fields from a bTree header
 *
 * used mainly for debug purposes
 */
void print_bTreeHeader(bTree_Header btree_head)
{
    printf("proxRRN: %d rootNODE: %d status: %c\n", btree_head.nextNodeRRN, btree_head.rootNode,
           btree_head.status);
}

/* bTree_Header
 *
 * -> Receive a bTree_Header struct (which information will be readed from the file) and a FILE
 pointer
 * (the buffer that will be readed)
 *
 * -> write the information from the file in *head following the order: "status", "rootNode",
 "nextNodeRRN"
 *
 * if the file is empty (no bytes were readed) return 0
 * if the file was succesfully readed, return 1
 *
 */
int bTree_readHeader(bTree_Header *head, FILE *file)
{
    fseek(file, 0, SEEK_SET);

    if (fread(&head->status, sizeof(char), 1, file) != 1)
        return 0;

    fread(&head->rootNode, sizeof(int), 1, file);
    fread(&head->nextNodeRRN, sizeof(int), 1, file);

    fseek(file, BTREE_DISK_PAGE_LEN - 9, SEEK_CUR);

    return 1;
}

/* Btree_writeHeader
 *
 * -> Receive a bTreeHeader struct (which information will be put on the file) and a FILE pointer
 (the
 * buffer that it will write on)
 *
 * -> write the information in *head in the file in the following order: "status", "rootNODE",
 "nextNodeRRN"
 *
 * should be called only if the bTree file is not created yet
 *
 */
int bTree_writeHeader(bTree_Header *head, FILE *file)
{
    fwrite(&head->status, sizeof(char), 1, file);
    fwrite(&head->rootNode, sizeof(int), 1, file);
    fwrite(&head->nextNodeRRN, sizeof(int), 1, file);

    char aux = '$';
    for (int i = 0; i < BTREE_DISK_PAGE_LEN - 9; i++)
        fwrite(&aux, sizeof(char), 1, file);
    return 1;
}

/* Btree_writeHeader
 *
 * -> Receive a bTreeHeader struct (which information will be put on the file) and a FILE pointer
 (the
 * buffer that it will write on)
 *
 * -> write the information in *head in the file in the following order: "status", "rootNODE",
 "nextNodeRRN"
 *
 * Must be called only if the bTree index file already exists
 *
 */
int bTree_updateHeader(bTree_Header *head, FILE *file)
{
    int save = ftell(file);

    fseek(file, 0, SEEK_SET);

    fwrite(&head->status, sizeof(char), 1, file);
    fwrite(&head->rootNode, sizeof(int), 1, file);
    fwrite(&head->nextNodeRRN, sizeof(int), 1, file);

    fseek(file, save, SEEK_SET);
    return 1;
}
