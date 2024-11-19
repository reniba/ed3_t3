#include "./../headers/graphRoutines.h"

// comparator to determine a comparasion rule for the data types created
inline bool operator<(const NAME_NODE &a, const NAME_NODE &b)
{
    return a.name < b.name;
}

inline bool operator<(const FOOD_NODE &a, const FOOD_NODE &b)
{
    return a.food < b.food;
}
inline bool operator<(const std::pair<NAME_NODE, std::vector<FOOD_NODE>> &a,
                      const std::pair<NAME_NODE, std::vector<FOOD_NODE>> &b)
{
    return a.first.name < b.first.name;
}

// create a temporary NAME_NODE given the prey name
//
// used when a prey is inserted, but not initialized as a hunter
NAME_NODE createTemporaryNameNode(std::string name)
{
    NAME_NODE temp_node;
    temp_node.name = name;
    temp_node.degree = 0;
    temp_node.entry_degree = 0;
    temp_node.exit_degree = 0;
    return temp_node;
}

// create a NAME_NODE given a struct Dinosaur given
//
// used when a hunter is inserted in the graph and was not initized yet
NAME_NODE createNameNode(Dinosaur temp_dino)
{
    NAME_NODE temp_node;
    temp_node.name = temp_dino.name;
    temp_node.species = temp_dino.specie_name;
    temp_node.habitat = temp_dino.habitat;
    temp_node.diet = temp_dino.diet;
    temp_node.type = temp_dino.type;
    temp_node.entry_degree = temp_node.exit_degree = temp_node.degree = 0;
    return temp_node;
}
// create a FOOD_NODE
//
// used when a prey is inserted as a "food" from other hunter
FOOD_NODE createFoodNode(Dinosaur temp_dino)
{
    FOOD_NODE temp_node;
    temp_node.food = temp_dino.food;
    temp_node.population = temp_dino.population;
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
    // if food is null, the prey and hunter are not part of the food chain
    if (!strlen(temp_dino.food))
    {
        return;
    }

    // search to check if the predator already exists in the graph
    bool found_predator = false;
    int predator_position = -1;
    for (int i = 0; i < graph->size(); i++)
    {
        if ((*graph)[i].first.name == temp_dino.name)
        {
            found_predator = true;
            predator_position = i;
        }
    }

    if (found_predator)
    {
        // check if the predator has been initialized as prey
        if ((*graph)[predator_position].second.empty())
        {
            // predator found but not initialized - initialize it

            NAME_NODE temp_name_node = createNameNode(temp_dino);

            // saving the degree of past insertions
            int temp_degree1 = ((*graph)[predator_position].first).degree;
            int temp_degree2 = ((*graph)[predator_position].first).entry_degree;

            // setting NAME_NODE
            (*graph)[predator_position].first = temp_name_node;
            (*graph)[predator_position].first.degree += temp_degree1;
            (*graph)[predator_position].first.entry_degree += temp_degree2;
            increaseExitlevel(graph, (*graph)[predator_position].first.name);

            // setting VECTOR_NODE
            FOOD_NODE temp_food_node = createFoodNode(temp_dino);
            ((*graph)[predator_position].second.push_back(temp_food_node));
        }
        else
        {
            // predator found and already initialized

            // setting NAME_NODE
            increaseExitlevel(graph, (*graph)[predator_position].first.name);

            // setting FOOD_NODE
            FOOD_NODE temp_food_node = createFoodNode(temp_dino);
            ((*graph)[predator_position].second.push_back(temp_food_node));
        }
    }
    else
    {
        // predator not found - add as a new node

        // setting NAME_NODE
        NAME_NODE temp_name_node = createNameNode(temp_dino);

        // setting FOOD_NODE
        FOOD_NODE temp_food_node = createFoodNode(temp_dino);
        std::vector<FOOD_NODE> temp_vector;
        temp_vector.push_back(temp_food_node);
        (*graph).push_back(std::make_pair(temp_name_node, temp_vector));

        // increasing NAME_NODE
        increaseExitlevel(graph, temp_name_node.name);
    }

    // adding prey to the graph
    // finding location of the food/prey
    bool found_prey = false;
    int prey_position = -1;
    for (int i = 0; i < graph->size(); i++)
    {
        if ((*graph)[i].first.name == temp_dino.food)
        {
            found_prey = true;
            prey_position = i;
        }
    }

    if (found_prey)
    {
        // prey found
        // setting NAME_NODE
        increaseEntrylevel(graph, (*graph)[prey_position].first.name);
    }
    else
    {
        // prey not found - add as a new node
        // setting NAME_NODE
        NAME_NODE temp_name_node = createTemporaryNameNode(temp_dino.food);

        // setting FOOD_NODE
        std::vector<FOOD_NODE> temp_vector = {};
        (*graph).push_back(std::make_pair(temp_name_node, temp_vector));

        // setting NAME_NODE
        increaseEntrylevel(graph, temp_name_node.name);
    }
}

/*
 * sorts the graph and its internal adjacent lists according to, respectively, the name representing
 the node and the food representing the node
 */
void sortGraph(GRAPH *graph)
{
    // sort each inner vector in the graph
    for (int i = 0; i < graph->size(); i++)
    {
        if (!(*graph)[i].second.empty()) // if not empty
            sort((*graph)[i].second.begin(), (*graph)[i].second.end());
    }
    // sort the main graph vector
    sort((*graph).begin(), (*graph).end());
}

/*
 * shows the node of position i, j.
 */
void printNode(GRAPH *temp_graph, int i, int j)
{
    printf("%s %s %s %s %s %d %d %d %s %d\n", (*temp_graph)[i].first.name.c_str(),
           (*temp_graph)[i].first.species.c_str(), (*temp_graph)[i].first.habitat.c_str(),
           (*temp_graph)[i].first.diet.c_str(), (*temp_graph)[i].first.type.c_str(),
           (*temp_graph)[i].first.entry_degree, (*temp_graph)[i].first.exit_degree,
           (*temp_graph)[i].first.degree, (*temp_graph)[i].second[j].food.c_str(),
           (*temp_graph)[i].second[j].population);
}

/*
 * shows the entire graph.
 */
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
/*
 * initializes a graph from a binary file containing information about dinosaurs
 */
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

    // insert each register into graph
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
