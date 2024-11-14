#include "./../../headers/func_12.h"

int funcionality12(char DinosaurData_filename[], char input[])
{
    // initialize graph
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);
    AUX_INDEX_MAP IndexMap = setIndexMap(&graph);

    std::cout << "Quantidade de ciclos: " << find_number_of_cycles(&graph, &IndexMap) << std::endl;

    return EXIT_SUCCESS;
}
