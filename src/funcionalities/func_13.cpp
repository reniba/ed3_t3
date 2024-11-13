// para cada vértice do grafo
// realize uma dfs
//
// se a dfs retornar ao nó inicial +1;
//
// adicionar esse vértice como marcado
//
// realizar dfs novamente sem passar pelos nós marcados
//
#include "./../../headers/func_13.h"
#include <algorithm>
#include <cstdio>
#include <initializer_list>
#include <utility>

// INSERT funcionality
int funcionality13(char DinosaurData_filename[])
{
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);
    // printGraph(&graph);
    AUX_INDEX_MAP IndexMap = setIndexMap(&graph);
    // cout << IndexMap["abelisaurus"] << endl;
    // printGraph(&graph);
    // dfs(&graph, &IndexMap);
    // GRAPH transposed_graph;
    // initializeTranposedGraph(&graph, &transposed_graph, &IndexMap);
    // printGraph(&transposed_graph);
    bool strong = isStronglyConnected(&graph, &IndexMap);
    std::cout << (strong ? "Sim, o grafo é fortemente conexo"
                         : "Não, o grafo não é fortemente conexo")
              << " e possui " << StrongCompsGraph(&graph, &IndexMap) << " componentes."
              << std::endl;
    //  std::endl;

    return EXIT_SUCCESS;
}
