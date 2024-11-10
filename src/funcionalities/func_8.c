#include "./../../headers/func_8.h"
#include <stdlib.h>

// SELECT funcionality
int funcionality8(char DinosaurData_filename[], char BtreeIndex_filename[])
{
    // input
    char field[MAX_FIELD_LEN], value[MAX_VALUE_LEN];
    scanf("%s", field);
    scan_quote_string(value);

    // opening files
    FILE *index_file, *data_file;
    index_file = fopen(BtreeIndex_filename, "rb");
    data_file = fopen(DinosaurData_filename, "rb");
    if (!index_file || !data_file)
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

    // search for byte_offset in index file
    long byte_offset = searchRRN(btree_head.rootNode, converteNome(value), index_file);

    // if RRN was not found
    if (byte_offset == NOT_FOUND)
    {
        msg_no_registers();
        return EXIT_SUCCESS;
    }

    // if RRN was found
    Dinosaur temp_dino;

    // byte_offset = 160*rrn + 1600
    // rrn = (byte_offset-1600)/160
    ReadFromFileRRN(&temp_dino, data_file, (byte_offset - DISK_PAGE_LEN) / REGISTER_LEN);
    printDino(temp_dino);

    // finish funcionality
    fclose(data_file);
    fclose(index_file);

    return EXIT_SUCCESS;
}
