#include "../../headers/func_7.h"

// CREATE INDEX B TREE
int funcionality7(char inputFileName[], char bTreeFileName[])
{
    // opening files
    FILE *file_in, *file_out;
    file_in = fopen(inputFileName, "rb");
    file_out = fopen(bTreeFileName, "wb+");
    if (!file_in || !file_out)
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // read header informations and save it on "head"
    Header head;
    if (readHeader(&head, file_in) == 0) // empty file
    {
        msg_default_error();
        return EXIT_FAILURE;
    };
    if (head.status == '0') // inconsistent file
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // initializing btree head
    bTree_Header btree_head = initializeBtreeHeader();
    bTree_writeHeader(&btree_head, file_out);

    // finding first not removed register and saving its position into count
    Dinosaur temp_dino;
    int count = 0;
    while (1)
    {
        if (ReadFromFileRRN(&temp_dino, file_in, count) == 0)
        {
            // if no register were found
            fclose(file_in);
            fclose(file_out);
            binarioNaTela(bTreeFileName);
            return EXIT_SUCCESS;
        }
        if (temp_dino.removed == '0')
            break;
        count++;
    }

    // inserting root node
    KEY key = {converteNome(temp_dino.name),
               DISK_PAGE_LEN + (count * REGISTER_LEN)}; // initializing key
    PAGE temp_page = inititializePage(&btree_head);     // initializing page

    // inserting into position 0 and right child = NULL_NODE
    insertKeyintoNode(&temp_page, key, NULL_NODE, 0);
    writeBtreeIndexPage(&temp_page, 0, file_out); // writing at file

    // updating header
    btree_head.nextNodeRRN = 1;
    btree_head.rootNode = 0;

    // inserting other keys
    int ROOT = btree_head.rootNode;
    for (int i = 1; i < head.nextRRN; i++)
    {
        // reading from file and setting variables for insert
        ReadFromFileRRN(&temp_dino, file_in, i);
        KEY key = {converteNome(temp_dino.name), DISK_PAGE_LEN + (i * REGISTER_LEN)};

        int PROMO_R_CHILD;
        KEY PROMO_KEY;
        if (temp_dino.removed == '0') // if the register readed is not removed
        {
            if (insert(btree_head.rootNode, key, &PROMO_R_CHILD, &PROMO_KEY, file_out,
                       &btree_head) == PROMOTION) // try to insert it
            {
                // if the return is PROMOTION, make a split at root
                PAGE NEWROOT = inititializePage(&btree_head);
                NEWROOT.keys[0] = PROMO_KEY;
                NEWROOT.children[0] = btree_head.rootNode;
                NEWROOT.children[1] = PROMO_R_CHILD;
                NEWROOT.NumIndexedKeys = 1;
                NEWROOT.leaf = '0';

                // update header informations
                btree_head.rootNode = NEWROOT.RRNnode;
                writeBtreeIndexPage(&NEWROOT, NEWROOT.RRNnode, file_out);
            }
        }
    }

    // update header in file
    btree_head.status = '1';
    bTree_updateHeader(&btree_head, file_out);

    fclose(file_in);
    fclose(file_out);

    binarioNaTela(bTreeFileName);

    return EXIT_SUCCESS;
}
