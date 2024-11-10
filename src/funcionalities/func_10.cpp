#include "./../../headers/func_10.h"

// INSERT funcionality
int funcionality10(char DinosaurData_filename[])
{
    // opening files for insertion
    FILE *data_file;
    data_file = fopen(DinosaurData_filename, "rb");
    if (!data_file)
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
    // initialize grapgh
    GRAPH graph;

    // input amount of items to insert
    char input[MAX_VALUE_LEN];
    scanf("%s", input);

    for (int i = 1; i <= atoi(input); i++)
    {
        // register input
        Dinosaur temp_dino;
        readFromInput(&temp_dino);

        // add grapgh
    }

    fclose(data_file);

    // printGrapgh

    return EXIT_SUCCESS;
}
