#include "./../../headers/func_13.h"

int funcionality13(char DinosaurData_filename[])
{
    // initialize graph
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);
    AUX_INDEX_MAP index_map = setIndexMap(&graph);

    // bool strong = isStronglyConnected(&graph, &IndexMap);
    bool strong = kosaraju(&graph, &index_map);

    // output
    std::cout << (strong ? "Sim, o grafo é fortemente conexo"
                         : "Não, o grafo não é fortemente conexo")
              << " e possui " << kosaraju_number(&graph, &index_map) << " componentes."
              << std::endl;

    return EXIT_SUCCESS;
}
