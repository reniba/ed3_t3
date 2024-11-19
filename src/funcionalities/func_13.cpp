#include "./../../headers/func_13.h"

int funcionality13(char DinosaurData_filename[])
{
    // initialize graph
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);

    // verifying if the graph is strongly connected
    bool strong = kosaraju(&graph);

    // output
    std::cout << (strong ? "Sim, o grafo é fortemente conexo"
                         : "Não, o grafo não é fortemente conexo")
              << " e possui " << kosaraju_number(&graph) << " componentes." << std::endl;

    return EXIT_SUCCESS;
}
