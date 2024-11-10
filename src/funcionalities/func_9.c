#include "./../../headers/func_9.h"
#include <stdlib.h>

// INSERT funcionality
int funcionality9(char DinosaurData_filename[], char BtreeIndex_filename[])
{
    // opening files for insertion
    FILE *data_file, *index_file;
    data_file = fopen(DinosaurData_filename, "rb+");
    index_file = fopen(BtreeIndex_filename, "rb+");
    if (!data_file || !index_file)
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // read the data file header information
    Header head;
    if (readHeader(&head, data_file) == 0) // empty file
    {
        msg_default_error();
        return EXIT_FAILURE;
    };
    if (head.status == '0') // inconsistent file
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // read bTree header informations
    bTree_Header btree_head;
    if (bTree_readHeader(&btree_head, index_file) == 0) // empty file
    {
        msg_default_error();
        return EXIT_FAILURE;
    }
    if (btree_head.status == '0') // inconsistent file
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // modifying the file
    head.status = '0';
    btree_head.status = '0';

    // input amount of items to insert
    char input[MAX_VALUE_LEN];
    scanf("%s", input);

    for (int i = 1; i <= atoi(input); i++)
    {
        // register input
        Dinosaur temp_dino;
        readFromInput(&temp_dino);

        // verifying if the key is already inserted
        int FOUND_RRN, FOUND_POS;
        if (search(btree_head.rootNode, converteNome(temp_dino.name), &FOUND_RRN, &FOUND_POS,
                   index_file) == 1)
        {
            continue;
        }

        // insert on normal file
        // insert on the end of file
        int RRN;
        if (head.top == -1)
        {
            RRN = head.nextRRN;
            writeDinoRRN(RRN, data_file, &temp_dino);
            // update header informations
            head.nextRRN += 1;
            head.diskPageNum = ((head.nextRRN + 9) / 10) + 1;
        }
        // insert on the top of the "removed stack"
        else
        {
            RRN = head.top;
            head.top = searchNextChain(RRN, data_file);
            // updating header informations
            writeDinoRRN(RRN, data_file, &temp_dino);
            head.remRegNum -= 1;
        }

        // insert on BTREE
        KEY key = {converteNome(temp_dino.name), DISK_PAGE_LEN + (RRN * REGISTER_LEN)};
        int PROMO_R_CHILD;
        KEY PROMO_KEY;
        if (insert(btree_head.rootNode, key, &PROMO_R_CHILD, &PROMO_KEY, index_file, &btree_head) ==
            PROMOTION) // try to insert it
        {
            // if the return is PROMOTION, make a split at root
            PAGE NEWROOT = inititializePage(&btree_head);
            NEWROOT.keys[0] = PROMO_KEY;
            NEWROOT.children[0] = btree_head.rootNode;
            NEWROOT.children[1] = PROMO_R_CHILD;
            NEWROOT.NumIndexedKeys = 1;
            NEWROOT.leaf = '0';

            // updating header informations
            btree_head.rootNode = NEWROOT.RRNnode;
            writeBtreeIndexPage(&NEWROOT, NEWROOT.RRNnode, index_file);
        }

        // update header informations
        updateHeader(&head, data_file);
        bTree_updateHeader(&btree_head, index_file);
    }

    // finished modifying the file
    head.status = '1';
    btree_head.status = '1';
    updateHeader(&head, data_file);
    bTree_updateHeader(&btree_head, index_file);

    fclose(data_file);
    fclose(index_file);

    binarioNaTela(BtreeIndex_filename);
    return EXIT_SUCCESS;
}
