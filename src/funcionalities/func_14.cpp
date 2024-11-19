#include "./../../headers/func_14.h"

int funcionality14(char DinosaurData_filename[], char input[])
{
    // initialize GRAPH
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);

    // for each input
    for (int i = 0; i < atoi(input); i++)
    {
        // read feom stdin
        char field1[MAX_FIELD_LEN], field2[MAX_FIELD_LEN];
        scan_quote_string(field1);
        scan_quote_string(field2);
        std::string src = field1;
        std::string dest = field2;

        // search for a path beetween the input names
        bool ispath = isPath(&graph, src, dest);

        // output
        std::cout << src << " " << dest << ": "
                  << (ispath ? std::to_string((minPopulation(&graph, src, dest)))
                             : "CAMINHO INEXISTENTE")
                  << std::endl;
    }
    return EXIT_SUCCESS;
}
