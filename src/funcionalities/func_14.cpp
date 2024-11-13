// para cada vértice do grafo
// realize uma dfs
//
// se a dfs retornar ao nó inicial +1;
//
// adicionar esse vértice como marcado
//
// realizar dfs novamente sem passar pelos nós marcados
//
#include "./../../headers/func_14.h"
#include <algorithm>
#include <cstdio>
#include <initializer_list>
#include <string>
#include <utility>

// INSERT funcionality
int funcionality14(char DinosaurData_filename[], char input[])
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
    for (int i = 0; i < atoi(input); i++)
    {
        char field1[MAX_FIELD_LEN], field2[MAX_FIELD_LEN];
        scan_quote_string(field1);
        scan_quote_string(field2);
        std::string src = field1;
        std::string dest = field2;
        bool ispath = isPath(&graph, &IndexMap, src, dest);
        std::cout << src << " " << dest << ": "
                  << (ispath ? std::to_string((minPopulation(&graph, src, dest, &IndexMap)))
                             : "CAMINHO INEXISTENTE")
                  << std::endl;
    }
    return EXIT_SUCCESS;
}
