#include "./../headers/graphRoutines.h"
#include <cmath>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
//#include <cstdlib>
//#include <cstring>
//#include <string>
//#include <vector>

inline bool operator<(const ARRAY_NODE &a, const ARRAY_NODE &b)
{
    return a.name < b.name;
}

inline bool operator<(const VECTOR_NODE &a, const VECTOR_NODE &b)
{
    return a.food < b.food;
}
inline bool operator<(const std::pair<ARRAY_NODE, std::vector<VECTOR_NODE>> &a,
                      const std::pair<ARRAY_NODE, std::vector<VECTOR_NODE>> &b)
{
    return a.first.name < b.first.name;
}

ARRAY_NODE createTEMParrayNode(std::string name)
{
    ARRAY_NODE temp_node;
    temp_node.name = name;
    temp_node.degree = 0;
    temp_node.entry_degree = 0;
    temp_node.exit_degree = 0; // flag
    return temp_node;
}

ARRAY_NODE createArrayNode(Dinosaur temp_dino)
{
    ARRAY_NODE temp_node;
    temp_node.name = temp_dino.name;
    temp_node.species = temp_dino.specie_name;
    temp_node.habitat = temp_dino.habitat;
    temp_node.diet = temp_dino.diet;
    temp_node.type = temp_dino.type;
    temp_node.entry_degree = temp_node.exit_degree = temp_node.degree = 0;
    return temp_node;
}
VECTOR_NODE createVectorNode(Dinosaur temp_dino)
{
    VECTOR_NODE temp_node;
    temp_node.food = temp_dino.food;
    temp_node.population = temp_dino.population;
    temp_node.name = temp_dino.name;
    return temp_node;
}

void increaseEntrylevel(GRAPH *graph, std::string name)
{
    for (int i = 0; i < graph->size(); i++)
    {
        if ((*graph)[i].first.name == name)
        {
            ((*graph)[i].first).entry_degree++;
            ((*graph)[i].first).degree++;
        }
    }
}
void increaseExitlevel(GRAPH *graph, std::string name)
{
    for (int i = 0; i < graph->size(); i++)
    {
        if ((*graph)[i].first.name == name)
        {
            ((*graph)[i].first).exit_degree++;
            ((*graph)[i].first).degree++;
        }
    }
}

void addGraph(GRAPH *graph, Dinosaur temp_dino)
{
    bool found_predator = false;
    bool found_prey = false;
    int found_pos_predator = -1;
    int found_pos_prey = -1;
    for (int i = 0; i < graph->size(); i++)
    {
        if ((*graph)[i].first.name == temp_dino.name)
        {
            found_predator = true;
            found_pos_predator = i;
        }
        if ((*graph)[i].first.name == temp_dino.food)
        {
            found_prey = true;
            found_pos_prey = i;
        }
    }
    // std::cout << temp_dino.name << std::endl;
    // std::cout << temp_dino.food << std::endl;
    // std::cout << found_predator << " " << found_prey << std::endl;
    if (!strlen(temp_dino.food))
    {
        return;
    }
    if (found_predator)
    {
        // precisa checar o se predator ja foi inicializado como prey
        if ((*graph)[found_pos_predator].second.empty())
        {
            ARRAY_NODE temp_node = createArrayNode(temp_dino);

            int temp1 = ((*graph)[found_pos_predator].first).entry_degree;
            int temp2 = ((*graph)[found_pos_predator].first).degree;

            (*graph)[found_pos_predator].first = temp_node;
            (*graph)[found_pos_predator].first.degree += temp2;
            (*graph)[found_pos_predator].first.entry_degree += temp1;
            // increaseExitlevel(graph, temp_dino.name);
            //             (*graph)[found_pos_predator].first = temp_node;
        }

        // dino que come está no grafo mas inicializado
        VECTOR_NODE temp_node = createVectorNode(temp_dino);

        ((*graph)[found_pos_predator].second.push_back(temp_node));
        increaseExitlevel(graph, (*graph)[found_pos_predator].first.name);
    }
    else
    {
        // precisa checar o se predator ja foi inicializado como prey
        // dino que come está no grafo mas inicializado
        VECTOR_NODE temp_node = createVectorNode(temp_dino);
        ARRAY_NODE temp_node2 = createArrayNode(temp_dino);
        std::vector<VECTOR_NODE> temp_vector;
        temp_vector.push_back(temp_node);
        (*graph).push_back(std::make_pair(temp_node2, temp_vector));

        increaseExitlevel(graph, temp_node.name);
    }
    if (found_prey)
    {
        // precisa checar o se predator ja foi inicializado como prey
        increaseEntrylevel(graph, (*graph)[found_pos_prey].first.name);
    }
    else
    {
        // precisa checar o se predator ja foi inicializado como prey
        ARRAY_NODE temp_node3 = createTEMParrayNode(temp_dino.food);
        // VECTOR_NODE temp_node = createVectorNode(temp_dino);
        ////ARRAY_NODE temp_node2 = createArrayNode(temp_dino);
        std::vector<VECTOR_NODE> temp_vector = {};
        //(*graph)->second.push_back(temp_vector);
        // graph->first.push_back(temp_node3);
        (*graph).push_back(std::make_pair(temp_node3, temp_vector));

        increaseEntrylevel(graph, temp_node3.name);
    }
}

void sortGraph(GRAPH *graph)
{
    // for each line , sort the vector inside
    // sort all the main vector
    for (int i = 0; i < graph->size(); i++)
    {
        if (!(*graph)[i].second.empty())
            sort((*graph)[i].second.begin(), (*graph)[i].second.end());
    }
    sort((*graph).begin(), (*graph).end());
    // sort((*graph).array_node.begin(), (*graph).array_node.end());
}

void printNode(GRAPH *temp_graph, int i, int j)
{
    printf("%s %s %s %s %s %d %d %d %s %d\n", (*temp_graph)[i].first.name.c_str(),
           (*temp_graph)[i].first.species.c_str(), (*temp_graph)[i].first.habitat.c_str(),
           (*temp_graph)[i].first.diet.c_str(), (*temp_graph)[i].first.type.c_str(),
           (*temp_graph)[i].first.entry_degree, (*temp_graph)[i].first.exit_degree,
           (*temp_graph)[i].first.degree, (*temp_graph)[i].second[j].food.c_str(),
           (*temp_graph)[i].second[j].population);
}

void printGraph(GRAPH *graph)
{
    for (int i = 0; i < (*graph).size(); i++)
    {
        for (int j = 0; j < (*graph)[i].second.size(); j++)
        {
            printNode(graph, i, j);
        }
    }
}
