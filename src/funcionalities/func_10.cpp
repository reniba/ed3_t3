#include "./../../headers/func_10.h"
#include <algorithm>

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
    for (int i = 1; i <= head.nextRRN; i++)
    // for (int i = 1; i <= 1; i++)
    {
        // register input
        Dinosaur temp_dino;
        ReadFromFile(&temp_dino, data_file);
        // if (temp_dino.population > -1)
        addGraph(&graph, temp_dino);
        //  add grapgh
    }
    sortGraph(&graph);
    printGraph(&graph);
    fclose(data_file);

    // printGrapgh

    return EXIT_SUCCESS;
}
