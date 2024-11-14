#include "./../headers/graphRoutines.h"

// comparator to determine a comparasion rule for the data types created
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

// create a temporary ARRAY_NODE given the prey name
//
// used when a prey is inserted, but not initialized as a hunter
ARRAY_NODE createTEMParrayNode(std::string name)
{
    ARRAY_NODE temp_node;
    temp_node.name = name;
    temp_node.degree = 0;
    temp_node.entry_degree = 0;
    temp_node.exit_degree = 0;
    return temp_node;
}

// create a ARRAY_NODE given a struct Dinosaur given
//
// used when a hunter is inserted in the graph and was not initized yet
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
// create a VECTOR_NODE
//
// used when a prey is inserted as a "food" from other hunter
VECTOR_NODE createVectorNode(Dinosaur temp_dino)
{
    VECTOR_NODE temp_node;
    temp_node.food = temp_dino.food;
    temp_node.population = temp_dino.population;
    temp_node.name = temp_dino.name;
    return temp_node;
}

// increments the entry degree and overall degree of a node given its name in the graph
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

// Increments the exit degree and degree of a node given its name in the graph
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

// inserts a new record into the graph
void addGraph(GRAPH *graph, Dinosaur temp_dino)
{
    // search to check if the predator already exists in the graph
    bool found_predator = false;
    int found_pos_predator = -1;
    for (int i = 0; i < graph->size(); i++)
    {
        if ((*graph)[i].first.name == temp_dino.name)
        {
            found_predator = true;
            found_pos_predator = i;
        }
    }
    // se food is null, the prey and hunter are not part of the food chain
    if (!strlen(temp_dino.food))
    {
        return;
    }
    if (found_predator)
    {
        // check if the predator has been initialized as prey
        if ((*graph)[found_pos_predator].second.empty())
        {
            // predator found but not initialized - initialize it
            ARRAY_NODE temp_node = createArrayNode(temp_dino);

            int temp1 = ((*graph)[found_pos_predator].first).entry_degree;
            int temp2 = ((*graph)[found_pos_predator].first).degree;

            (*graph)[found_pos_predator].first = temp_node;
            (*graph)[found_pos_predator].first.degree += temp2;
            (*graph)[found_pos_predator].first.entry_degree += temp1;
            VECTOR_NODE temp_node2 = createVectorNode(temp_dino);

            ((*graph)[found_pos_predator].second.push_back(temp_node2));
            increaseExitlevel(graph, (*graph)[found_pos_predator].first.name);
        }
        else
        {
            // predator found and already initialized
            VECTOR_NODE temp_node = createVectorNode(temp_dino);
            ((*graph)[found_pos_predator].second.push_back(temp_node));
            increaseExitlevel(graph, (*graph)[found_pos_predator].first.name);
        }
    }
    else
    {
        // predator not found - add as a new node
        VECTOR_NODE temp_node = createVectorNode(temp_dino);
        ARRAY_NODE temp_node2 = createArrayNode(temp_dino);
        std::vector<VECTOR_NODE> temp_vector;
        temp_vector.push_back(temp_node);
        (*graph).push_back(std::make_pair(temp_node2, temp_vector));

        increaseExitlevel(graph, temp_node.name);
    }

    // add pay to the graph
    bool found_prey = false;
    int found_pos_prey = -1;
    for (int i = 0; i < graph->size(); i++)
    {

        if ((*graph)[i].first.name == temp_dino.food)
        {
            found_prey = true;
            found_pos_prey = i;
        }
    }
    if (found_prey)
    {
        // prey found
        increaseEntrylevel(graph, (*graph)[found_pos_prey].first.name);
    }
    else
    {
        // prey not found - add as a new node
        ARRAY_NODE temp_node3 = createTEMParrayNode(temp_dino.food);
        std::vector<VECTOR_NODE> temp_vector = {};
        (*graph).push_back(std::make_pair(temp_node3, temp_vector));

        increaseEntrylevel(graph, temp_node3.name);
    }
}

// sort the graph nodes and their internal vectors
void sortGraph(GRAPH *graph)
{
    // sort each inner vector in the graph
    for (int i = 0; i < graph->size(); i++)
    {
        if (!(*graph)[i].second.empty())
            sort((*graph)[i].second.begin(), (*graph)[i].second.end());
    }
    // sort the main graph vector
    sort((*graph).begin(), (*graph).end());
}

// prints a single node and its data
void printNode(GRAPH *temp_graph, int i, int j)
{
    printf("%s %s %s %s %s %d %d %d %s %d\n", (*temp_graph)[i].first.name.c_str(),
           (*temp_graph)[i].first.species.c_str(), (*temp_graph)[i].first.habitat.c_str(),
           (*temp_graph)[i].first.diet.c_str(), (*temp_graph)[i].first.type.c_str(),
           (*temp_graph)[i].first.entry_degree, (*temp_graph)[i].first.exit_degree,
           (*temp_graph)[i].first.degree, (*temp_graph)[i].second[j].food.c_str(),
           (*temp_graph)[i].second[j].population);
}

// prints the entire graph.
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

// initializes the graph from a binary file containing dinosaur data.
void initializeGraph(GRAPH *graph, char Dinosaur_file[])
{
    FILE *data_file;
    data_file = fopen(Dinosaur_file, "rb");
    if (!data_file)
    {
        msg_default_error();
        return;
    }

    // read the data file header information
    Header head;
    if (readHeader(&head, data_file) == 0) // empty file
    {
        msg_default_error();
        return;
    }
    if (head.status == '0') // inconsistent file
    {
        msg_default_error();
        return;
    }

    // initialize the graph bases on the files's content.
    for (int i = 1; i <= head.nextRRN; i++)
    {
        Dinosaur temp_dino;
        ReadFromFile(&temp_dino, data_file);
        addGraph(graph, temp_dino);
    }
    // sort the graph after all nodes are added.
    sortGraph(graph);
    fclose(data_file);
}
