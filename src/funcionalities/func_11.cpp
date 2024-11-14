#include "./../../headers/func_11.h"

int funcionality11(char DinosaurData_filename[], char input[])
{
    // initialize graph and its index_map
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);
    AUX_INDEX_MAP IndexMap = setIndexMap(&graph);

    int query_num = atoi(input);
    for (int k = 0; k < query_num; k++)
    {
        // read input from stdin
        char aux1[MAX_FIELD_LEN];
        scan_quote_string(aux1);
        string aux = aux1;

        // string that will be printed
        string temp = aux + ":";
        // bool that determine if there is 1 or more predators
        bool empty = true;

        // loop through all graph
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph[i].second.size(); j++)
            {
                // search for the predatos
                if (graph[i].second[j].food == aux)
                {
                    empty = false;
                    temp += " ";
                    temp += graph[i].second[j].name;
                    temp += ",";
                }
            }
        }
        // print the answer
        if (!empty)
            cout << temp.substr(0, temp.size() - 1) << endl << endl;
        else
            cout << "Registro Inexistente." << endl << endl;
    }

    return EXIT_SUCCESS;
}
