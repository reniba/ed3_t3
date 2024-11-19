#include "./../../headers/func_10.h"

int funcionality10(char DinosaurData_filename[])
{
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);

    printGraph(&graph);

    return EXIT_SUCCESS;
}
