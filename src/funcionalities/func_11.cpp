#include "./../../headers/func_11.h"
#include <algorithm>

// INSERT funcionality
int funcionality11(char DinosaurData_filename[], char input[])
{
    // opening files for insertion
    FILE *data_file;
    data_file = fopen(DinosaurData_filename, "rb");
    if (!data_file)
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // read the data file header information
    Header head;
    if (readHeader(&head, data_file) == 0) // empty file
    {
        msg_default_error();
        return EXIT_FAILURE;
    };
    if (head.status == '0') // inconsistent file
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // initialize grapgh
    GRAPH graph;

    // input amount of items to insert
    for (int i = 1; i <= head.nextRRN; i++)
    // for (int i = 1; i <= 1; i++)
    {
        // register input
        Dinosaur temp_dino;
        ReadFromFile(&temp_dino, data_file);
        // if (temp_dino.population > -1)
        addGraph(&graph, temp_dino);
        //  add grapgh
    }
    sortGraph(&graph);
    // printGraph(&graph);
    fclose(data_file);

    int query_num = atoi(input);
    for (int k = 0; k < query_num; k++)
    {
        char aux1[MAX_FIELD_LEN];
        scan_quote_string(aux1);
        string aux = aux1;

        string temp = aux + ":";
        bool empty = true;
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph[i].second.size(); j++)
            {
                if (graph[i].second[j].food == aux)
                {
                    empty = false;
                    temp += " ";
                    temp += graph[i].second[j].name;
                    temp += ",";
                }
            }
        }
        if (!empty)
            cout << temp.substr(0, temp.size() - 1) << endl << endl;
        else
            cout << "Registro Inexistente." << endl << endl;
    }
    // printGrapgh

    return EXIT_SUCCESS;
}
