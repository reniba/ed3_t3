// para cada vértice do grafo
// realize uma dfs
//
// se a dfs retornar ao nó inicial +1;
//
// adicionar esse vértice como marcado
//
// realizar dfs novamente sem passar pelos nós marcados
//
#include "./../../headers/func_12.h"

// INSERT funcionality
int funcionality12(char DinosaurData_filename[], char input[])
{
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);
    // printGraph(&graph);
    AUX_INDEX_MAP IndexMap = setIndexMap(&graph);
    // cout << IndexMap["abelisaurus"] << endl;
    // printGraph(&graph);
    // dfs(&graph, &IndexMap);
    std::cout << "Quantidade de ciclos: " << dfs_number_of_cycles(&graph, &IndexMap) << std::endl;

    return EXIT_SUCCESS;
}
