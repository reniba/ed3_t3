#include "./../headers/bTreeRoutines.h"

/* printCurrentPage
 *
 * shows the contents of disk page passed as an argument.
 *
 * mostly used for DEBUG purposes.
 */
void printCurrentPage(PAGE temp_page)
{
    printf("%d | num_chaves: %d chaves: %ld %ld %ld %ld folha: %c\n filhos: %d %d %d %d %d \n",
           temp_page.RRNnode, temp_page.NumIndexedKeys, temp_page.keys[0].key,
           temp_page.keys[1].key, temp_page.keys[2].key, temp_page.keys[3].key, temp_page.leaf,
           temp_page.children[0], temp_page.children[1], temp_page.children[2],
           temp_page.children[3], temp_page.children[4]);
}

/* PrintCurrentWorkPage
 *
 * Same as PrintCurrentPage function, but shows the content of a WorkPage as defined in the lesson
 * slides.
 */
void printCurrentWorkPage(WORKING_PAGE temp_page)
{
    printf("%d | num_chaves: %d chaves: %ld %ld %ld %ld %ld folha: %c\n filhos: %d %d %d %d %d "
           "%d\n",
           temp_page.RRNnode, temp_page.NumIndexedKeys, temp_page.keys[0].key,
           temp_page.keys[1].key, temp_page.keys[2].key, temp_page.keys[3].key,
           temp_page.keys[4].key, temp_page.leaf, temp_page.children[0], temp_page.children[1],
           temp_page.children[2], temp_page.children[3], temp_page.children[4],
           temp_page.children[5]);
}

void printVariables(int P_B_RRN, KEY P_B_KEY, KEY PROMO_KEY, int PROMO_R_CHILD)
{
    printf("P_B_RRN: %d P_B_KEY: %ld PROMO_KEY: %ld PROMO_R_CHILD: %d\n", P_B_RRN, P_B_KEY.key,
           PROMO_KEY.key, PROMO_R_CHILD);
}

/* initializePage
 *
 * create an empty DiskPage.
 *
 * By default, this new page is a leaf node
 * and its RRN is determined by the "nextNodeRRN" information inside the bTree header.
 */
PAGE inititializePage(bTree_Header *btree_head)
{
    PAGE temp_page;
    temp_page.leaf = '1';
    temp_page.NumIndexedKeys = 0;
    temp_page.RRNnode = btree_head->nextNodeRRN;
    btree_head->nextNodeRRN += 1;
    // setting children
    for (int i = 0; i < ORDER; i++)
    {
        temp_page.children[i] = NULL_NODE;
    }
    // setting keys
    for (int i = 0; i < ORDER - 1; i++)
    {
        temp_page.keys[i].key = NULL_KEY;
        temp_page.keys[i].RRN = NULL_RRN;
    }
    return temp_page;
}

/* setWorkingPage
 *
 * Creates a WorkingPage as specified in classroom lessons nad PDFs.
 *
 * Receives a new KEY and RRN and place it on POS position of the page.
 *
 * P_B_KEY = key to inserted
 * P_B_RRN = right child from the key above
 * POS = position where the new key must be inserted
 */
WORKING_PAGE setWorkingPage(PAGE *temp_page, KEY I_KEY, int I_RRN, int POS)
{
    WORKING_PAGE temp_workpage;
    temp_workpage.RRNnode = -1;
    temp_workpage.NumIndexedKeys = temp_page->NumIndexedKeys + 1;
    temp_workpage.leaf = '0';

    // "insertion" algorithm
    temp_workpage.children[0] = temp_page->children[0];
    int jump = 0;
    for (int i = 0; i < ORDER; i++)
    {
        if (i != POS) // insert keys from the temporary page
        {
            temp_workpage.keys[i] = temp_page->keys[i - jump];
            temp_workpage.children[i + 1] = temp_page->children[i + 1 - jump];
        }
        else if (i == POS) // insert new KEY into POS position
        {
            temp_workpage.keys[POS] = I_KEY;
            temp_workpage.children[POS + 1] = I_RRN;
            jump = 1;
        }
    }
    return temp_workpage;
}

/* insertKeyintoNode
 *
 * Inserts a key into a PAGE (temp_page) that is not full.
 *
 * P_B_KEY = key to inserted
 * P_B_RRN = right child from the KEY above
 * POS = position where the new KEY must be inserted
 *
 */
int insertKeyintoNode(PAGE *temp_page, KEY P_B_KEY, int P_B_RRN, int POS)
{
    PAGE COPYPAGE = *temp_page;

    //"insertion" algorithm
    int jump = 0;
    for (int i = 0; i < ORDER - 1; i++)
    {
        if (i != POS) // insert keys from temp_page
        {
            temp_page->keys[i] = COPYPAGE.keys[i - jump];
            temp_page->children[i + 1] = COPYPAGE.children[i + 1 - jump];
        }
        else if (i == POS) // insert new key at POS position
        {
            temp_page->keys[POS] = P_B_KEY;
            temp_page->children[POS + 1] = P_B_RRN;
            jump = 1;
        }
    }
    temp_page->NumIndexedKeys++;
    return 1;
}

/* writeBtreeIndexPage
 *
 * writes a PAGE passed by reference into the index Btree file at the RRN passed to the function.
 *
 * temp_page = page to be written
 * RRN = RRN where place will be written
 * bTreePointer = pointer to the index file
 */
int writeBtreeIndexPage(PAGE *temp_page, int RRN, FILE *bTreePointer)
{
    int save = ftell(bTreePointer);
    fseek(bTreePointer, (RRN + 1) * BTREE_DISK_PAGE_LEN, SEEK_SET);

    fwrite(&temp_page->leaf, sizeof(char), 1, bTreePointer);
    fwrite(&temp_page->NumIndexedKeys, sizeof(int), 1, bTreePointer);
    fwrite(&temp_page->RRNnode, sizeof(int), 1, bTreePointer);

    for (int i = 0; i < ORDER - 1; i++)
    {
        fwrite(&temp_page->children[i], sizeof(int), 1, bTreePointer);
        fwrite(&temp_page->keys[i].key, sizeof(long), 1, bTreePointer);
        fwrite(&temp_page->keys[i].RRN, sizeof(long), 1, bTreePointer);
    }
    fwrite(&temp_page->children[ORDER - 1], sizeof(int), 1, bTreePointer);
    fseek(bTreePointer, save, SEEK_SET);
    return 1;
}

/* readBtreeIndexPage
 *
 * Reads the disk page at the passed RRN and store it in the disk_page passed by reference.
 *
 * temp_page = page where the content will be stored
 * RRN = RRN from the page that will be read
 * bTreePointer = index btree file pointer
 *
 */
int readBtreeIndexPage(PAGE *temp_page, int RRN, FILE *bTreePointer)
{
    int save = ftell(bTreePointer);
    fseek(bTreePointer, (RRN + 1) * BTREE_DISK_PAGE_LEN, SEEK_SET);

    fread(&temp_page->leaf, sizeof(char), 1, bTreePointer);
    fread(&temp_page->NumIndexedKeys, sizeof(int), 1, bTreePointer);
    fread(&temp_page->RRNnode, sizeof(int), 1, bTreePointer);

    for (int i = 0; i < ORDER - 1; i++)
    {
        fread(&temp_page->children[i], sizeof(int), 1, bTreePointer);
        fread(&temp_page->keys[i].key, sizeof(long), 1, bTreePointer);
        fread(&temp_page->keys[i].RRN, sizeof(long), 1, bTreePointer);
    }
    fread(&temp_page->children[ORDER - 1], sizeof(int), 1, bTreePointer);
    fseek(bTreePointer, save, SEEK_SET);
    return 1;
}

// search
//
// Searches for a key in the Btree Index file
//
// default return: FOUND = 1 or NOT FOUND = -1
//
// Variables return:
// FOUND_RRN -> RRN where the key was found (-1 if not)
// FOUND_POS -> position relative to the node where the key was found (-1 if not)

int search(int RRN, long KEY, int *FOUND_RRN, int *FOUND_POS, FILE *bTreePointer)
{

    // if the node is a leaf(base case)
    if (RRN == NULL_NODE)
    {
        *FOUND_RRN = -1;
        *FOUND_POS = -1;
        return NOT_FOUND;
    }

    // if not a leaf, search at this node
    PAGE temp_page;
    readBtreeIndexPage(&temp_page, RRN, bTreePointer);

    for (int i = 0; i < temp_page.NumIndexedKeys; i++)
    {
        // if the key was found
        if (temp_page.keys[i].key == KEY)
        {
            *FOUND_RRN = temp_page.RRNnode;
            *FOUND_POS = i;
            return FOUND;
        }

        // if the current key is smaller than search key, contiue
        else if (temp_page.keys[i].key < KEY)
        {
            continue;
        }

        // if current key is greater than the search key, search in the left child
        else
        {
            return search(temp_page.children[i], KEY, FOUND_RRN, FOUND_POS, bTreePointer);
        }
    }

    // if all the keys in page are smaller than search key, search on the last child
    return search(temp_page.children[temp_page.NumIndexedKeys], KEY, FOUND_RRN, FOUND_POS,
                  bTreePointer);
}

/* searchRRN
 *
 * similar to search, but return the pointer to the data file of the searched key.
 *
 * returns the pointer(byte offset) of the found key relative to the data file (-1 if not found)
 */
long searchRRN(int RRN, long KEY, FILE *bTreePointer)
{

    // if the node is a leaf(base case)
    if (RRN == NULL_NODE)
    {
        return NOT_FOUND;
    }

    PAGE temp_page;
    readBtreeIndexPage(&temp_page, RRN, bTreePointer);

    for (int i = 0; i < temp_page.NumIndexedKeys; i++)
    {
        // if the key was foud
        if (temp_page.keys[i].key == KEY)
        {
            return temp_page.keys[i].RRN;
        }
        // if the current key is smaller than the searh key, continue;
        else if (temp_page.keys[i].key < KEY)
        {
            continue;
        }

        // if the current key is greater than the search key, search in left child
        else
        {
            return searchRRN(temp_page.children[i], KEY, bTreePointer);
        }
    }

    // if all the keys in the node are smaller, search at rightmost child
    return searchRRN(temp_page.children[temp_page.NumIndexedKeys], KEY, bTreePointer);
}

/* SPLIT
 *
 * Receives a page and a key that was promoted.
 *
 * Split this page into two pages, properly setting the keys and children.
 * set PROMO_KEY and PROMO_R_CHILD to the key that was promoted.
 *
 * I_KEY -> new key to be inserted (key that was promoted)
 * I_RRN -> right child of the key that was inserted
 * CURRENT_PAGE -> current disk page
 * NEWPAGE -> new page that will be inserted into the file
 * PROMO_KEY -> key that will be/was promoted to the next level after the procedure is over
 * PROMO_R_CHILD -> right child RRN from the key that was/will be promoted to next level after the
 * procedure is over
 * bTreePointer -> reference to the BtreeIndex file
 * btree_head-> btree index file header
 * POS = position where the new key must be inserted
 */
void split(KEY I_KEY, int I_RRN, PAGE *CURRENT_PAGE, KEY *PROMO_KEY, int *PROMO_R_CHILD,
           PAGE *NEWPAGE, FILE *bTreePointer, int POS, bTree_Header btree_head)
{
    // Create and set up work page
    WORKING_PAGE temp_workpage;
    temp_workpage = setWorkingPage(CURRENT_PAGE, I_KEY, I_RRN, POS);

    // set PROMO_KEY and PROMO_R_CHILD
    *PROMO_KEY = temp_workpage.keys[(ORDER) / 2];
    *PROMO_R_CHILD = NEWPAGE->RRNnode;

    // separte the content from work page into the page and the newpage
    CURRENT_PAGE->children[0] = temp_workpage.children[0];
    for (int i = 0; i < ORDER / 2; i++)
    {
        CURRENT_PAGE->children[i] = temp_workpage.children[i];
        CURRENT_PAGE->keys[i] = temp_workpage.keys[i];
    }
    CURRENT_PAGE->children[ORDER / 2] = temp_workpage.children[ORDER / 2];

    // clear the rest of the current page
    KEY null_key = {NULL_KEY, NULL_RRN};
    for (int i = ORDER / 2; i < ORDER - 1; i++)
    {
        CURRENT_PAGE->children[i + 1] = NULL_NODE;
        CURRENT_PAGE->keys[i] = null_key;
    }
    CURRENT_PAGE->NumIndexedKeys = ORDER / 2;

    // set up the new page
    NEWPAGE->children[0] = temp_workpage.children[(ORDER / 2) + 1];
    for (int i = 0; i < (ORDER - 1) / 2; i++)
    {
        NEWPAGE->children[i + 1] = temp_workpage.children[i + 1 + (ORDER / 2) + 1];
        NEWPAGE->keys[i] = temp_workpage.keys[i + (ORDER / 2) + 1];
    }

    NEWPAGE->NumIndexedKeys = (ORDER - 1) / 2;
    // set the leaf status of the new page
    if (CURRENT_PAGE->leaf == '1')
        NEWPAGE->leaf = '1';
    else
        NEWPAGE->leaf = '0';
}

/* insert
 * Inserts a new key into the B-Tree index file.
 *  **THERE IS NO "SPLIT AT ROOT" THREATMENT.**
 *
 * returns of the 3 default returns PROMOTION=1, NO_PROMOTION=0;ERROR=-.)
 *
 *CURRENT_RRN -> Current RRN.
 *FUNCTION_KEY -> key to be inserted.
 *PROMO_KEY -> key that is promoted to the next level.
 * PROMO_R_CHILD -> right child RRN off the key that was promoted to a higher level.
 * P_B_RRN -> RRN promoted from lower level
 * P_B_KEY -> KEY promoted from lower level
 * PAGE ->  Current page.
 * NEWPAGE -> Page created if a split is called.
 * POS -> position where the new key must be placed.
 */
int insert(int CURRENT_RRN, KEY FUNCTION_KEY, int *PROMO_R_CHILD, KEY *PROMO_KEY,
           FILE *bTreePointer, bTree_Header *btree_head)
{
    int P_B_RRN = NULL_RRN;
    KEY P_B_KEY = {NULL_KEY, NULL_RRN};
    PAGE temp_page;
    int POS = -1;

    int RETURN_VALUE;

    // leaf node
    if (CURRENT_RRN == NULL_NODE)
    {
        *PROMO_KEY = FUNCTION_KEY;
        *PROMO_R_CHILD = NULL_NODE;
        return PROMOTION;
    }

    readBtreeIndexPage(&temp_page, CURRENT_RRN, bTreePointer);

    // search for POS, position where the new key should be
    for (int i = 0; i < temp_page.NumIndexedKeys; i++)
    {
        if (temp_page.keys[i].key == FUNCTION_KEY.key)
        {
            // stop insertion
            return ERROR;
        }
        else if (temp_page.keys[i].key < FUNCTION_KEY.key)
        {
            continue;
        }
        else if (temp_page.keys[i].key > FUNCTION_KEY.key)
        {
            POS = i;
            break;
        }
    }

    // if key was not found in this page
    if (POS == -1)
        POS = temp_page.NumIndexedKeys;

    // Recursively call insert
    RETURN_VALUE =
        insert(temp_page.children[POS], FUNCTION_KEY, &P_B_RRN, &P_B_KEY, bTreePointer, btree_head);

    // Bottom-up construction after recursion ends
    // Set the return variables correctly
    *PROMO_KEY = P_B_KEY;
    *PROMO_R_CHILD = P_B_RRN;

    // ERROR ou NO_PROMOTION
    if (RETURN_VALUE == NO_PROMOTION || RETURN_VALUE == ERROR)
    {
        return NO_PROMOTION;
    }
    // If there is promotion, but you can insert the key "normally"
    else if (temp_page.NumIndexedKeys < ORDER - 1)
    {
        insertKeyintoNode(&temp_page, P_B_KEY, P_B_RRN, POS);
        writeBtreeIndexPage(&temp_page, temp_page.RRNnode, bTreePointer);

        return NO_PROMOTION;
    }
    // If there is promotion, but the current page is full, and a split is necessary
    else
    {
        PAGE NEWPAGE = inititializePage(btree_head);

        split(P_B_KEY, P_B_RRN, &temp_page, PROMO_KEY, PROMO_R_CHILD, &NEWPAGE, bTreePointer, POS,
              *btree_head);

        writeBtreeIndexPage(&temp_page, temp_page.RRNnode, bTreePointer);
        writeBtreeIndexPage(&NEWPAGE, NEWPAGE.RRNnode, bTreePointer);

        return PROMOTION;
    }
}
