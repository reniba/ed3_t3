#include "./../../headers/func_11.h"

int funcionality11(char DinosaurData_filename[], char input[])
{
    // initialize graph
    GRAPH graph;
    initializeGraph(&graph, DinosaurData_filename);

    // for each query
    int query_num = atoi(input);
    for (int k = 0; k < query_num; k++)
    {
        // read input from stdin
        char aux_input[MAX_FIELD_LEN];
        scan_quote_string(aux_input);
        string food_string = aux_input;

        // string that will be printed
        string answer = food_string + ":";
        // bool that determine if there is 1 or more predators
        bool empty = true;

        // loop through all graph
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph[i].second.size(); j++)
            {
                // search for the predators
                if (graph[i].second[j].food == food_string)
                {
                    empty = false;
                    answer += " ";
                    answer += graph[i].first.name;
                    answer += ",";
                }
            }
        }
        // print the answer
        if (!empty)
            cout << answer.substr(0, answer.size() - 1) << endl << endl;
        else
            cout << "Registro Inexistente." << endl << endl;
    }

    return EXIT_SUCCESS;
}
