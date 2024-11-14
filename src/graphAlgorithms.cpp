#include "./../headers/graphAlgorithms.h"

/*
 * Creates a mapping from each vertex's name in the graph to its index position.
 *
 * Example: index_table['aardonyx'] = 0, where the position of the vertex representing the
 * dinosaur "aardonyx" is 0.
 *
 * used as a helper for implementing other algorithms.
 */
AUX_INDEX_MAP setIndexMap(GRAPH *graph)
{
    AUX_INDEX_MAP temp_map;
    for (int i = 0; i < graph->size(); i++)
    {
        temp_map.insert(std::make_pair((*graph)[i].first.name, i));
    }
    return temp_map;
}

/* initializes a transposed graph where each prey points to each of its hunters.
 *
 * used by algorithms that involve connected paths.
 */
void initializeTranposedGraph(GRAPH *graph, GRAPH *transposedGraph, AUX_INDEX_MAP *index_map)
{
    // Initialize all nodes in transposed graph
    for (int i = 0; i < graph->size(); i++)
    {
        std::vector<VECTOR_NODE> temp = {};
        (*transposedGraph).push_back(make_pair((*graph)[i].first, temp));
    }
    // add each hunter to the correct prey
    for (int i = 0; i < graph->size(); i++)
    {
        for (int j = 0; j < (*graph)[i].second.size(); j++)
        {
            std::string food_name = (*graph)[i].second[j].food;
            std::string hunter_name = (*graph)[i].second[j].name;
            VECTOR_NODE temp_node;
            temp_node.name = food_name;
            temp_node.food = hunter_name;
            int index = (*index_map)[food_name];
            (*transposedGraph)[index].second.push_back(temp_node);
        }
    }
    sortGraph(transposedGraph);
}

/*
 * a depth-first search (DFS) that returns 1 if there is a path from the "origin" node to the
 * "destination" node
 * returns 0 otherwise
 */
int recursive_dfs(GRAPH *graph, AUX_INDEX_MAP *index_map, std::vector<bool> *visited,
                  std::string current_node_name, std::string destination_node_name)
{
    // if the current node is the destination, path is found
    if (current_node_name == destination_node_name)
        return 1;

    int current_index = (*index_map)[current_node_name];
    (*visited)[current_index] = true; // mark the current node as visited

    // visit each adjacent node if it has not been visited
    for (VECTOR_NODE food_node : (*graph)[current_index].second)
    {
        int destination_index = (*index_map)[food_node.food];
        if ((*visited)[destination_index] == false)
            if (recursive_dfs(graph, index_map, visited, food_node.food, destination_node_name) ==
                1)
                return 1;
    }
    return 0;
}

/*
 *  Checks if there is a path from the source node to the destination node.
 *
 * Initializes the "recursive_dfs" function to perform the path search.
 */
int isPath(GRAPH *graph, AUX_INDEX_MAP *index_map, std::string src, std::string dest)
{
    std::vector<bool> visited(index_map->size(), false);
    return recursive_dfs(graph, index_map, &visited, src, dest);
}

/* DFS adapted to find the number of cycle components
 *
 * return the number of cycles that leave a vertex origin and arrive at itself
 */
int dfs_number_of_cycles_rec(GRAPH *graph, AUX_INDEX_MAP *index_map, std::vector<bool> *visited,
                             std::string current_node_name, std::string origin_node_name, int *ans)
{
    int current_index = (*index_map)[current_node_name];
    (*visited)[current_index] = true; // marking current node as visited

    for (VECTOR_NODE food_node : (*graph)[(*index_map)[current_node_name]].second)
    {
        // if the current node finds the origin_node, increment the answer
        if (food_node.food == origin_node_name)
            (*ans)++;

        // visit other nodes
        if (!(*visited)[(*index_map)[food_node.food]])
            dfs_number_of_cycles_rec(graph, index_map, visited, food_node.food, origin_node_name,
                                     ans);
    }
    return 0;
}

/*
 * Returns the number of cycles in the given directed graph
 */
int find_number_of_cycles(GRAPH *graph, AUX_INDEX_MAP *IndexMap)
{
    int cycles_num = 0;

    // each iteration count the number of path that leave the origin and arrives at itself
    for (int i = 0; i < graph->size(); i++)
    {
        std::vector<bool> visited(IndexMap->size(), false);
        int aux_ans = 0;
        dfs_number_of_cycles_rec(graph, IndexMap, &visited, (*graph)[i].first.name,
                                 (*graph)[i].first.name, &aux_ans);
        cycles_num += aux_ans;
    }

    return cycles_num;
}
/*
 * Auxiliary DFS function, marking in the boolean vector all nodes reachable from "current_node".
 */
void DFS_util(GRAPH *graph, std::vector<bool> *visited, AUX_INDEX_MAP *index_map,
              std::string current_node)
{
    // marking the node as visited
    (*visited)[(*index_map)[current_node]] = true;
    for (auto &neighbor : (*graph)[(*index_map)[current_node]].second)
    {
        // mark another nodes
        if (!(*visited)[(*index_map)[neighbor.food]])
            DFS_util(graph, visited, index_map, neighbor.food);
    }
}

/*
 * Checks if a graph is strongly connected using a variation of Kosaraju's algorithm.

 */
bool kosaraju(GRAPH *graph, AUX_INDEX_MAP *index_map)
{
    GRAPH transposedGraph;
    initializeTranposedGraph(graph, &transposedGraph, index_map);
    AUX_INDEX_MAP new_index_map = setIndexMap(&transposedGraph);

    std::vector<bool> visited(graph->size(), false);
    DFS_util(graph, &visited, index_map, (*graph)[0].first.name);
    for (int i = 0; i < (*graph).size(); i++)
        if (visited[i] == false)
            return false;

    for (int i = 0; i < (*graph).size(); i++)
        visited[i] = false;

    DFS_util(&transposedGraph, &visited, &new_index_map, (transposedGraph)[0].first.name);
    for (int i = 0; i < (*graph).size(); i++)
        if (visited[i] == false)
            return false;

    return true;
}
/*
 * Fill stack with vertices in increasing order of finishing times
 */
void fillOrder(GRAPH *graph, AUX_INDEX_MAP *index_map, std::string current_node,
               std::vector<bool> *visited, std::stack<int> *Stack)
{
    int current_index = (*index_map)[current_node];
    (*visited)[current_index] = true; // marking the node as visited

    // for each adjacent node
    for (auto &neighbor : (*graph)[current_index].second)
    {
        // if adjacent node is not visited
        if (!(*visited)[(*index_map)[neighbor.food]])
            fillOrder(graph, index_map, neighbor.food, visited, Stack);
    }
    // all vertices reachable from v are processed, push current node
    (*Stack).push(current_index);
}

/*
 * Calculate the number of strongly connected components using kosaraju's algorithm
 */
int kosaraju_number(GRAPH *graph, AUX_INDEX_MAP *index_map)
{
    int ans = 0;
    std::stack<int> Stack;
    std::vector<bool> visited(graph->size(), false);
    // fill vertives
    for (int i = 0; i < graph->size(); i++)
    {
        if (visited[i] == false)
            fillOrder(graph, index_map, (*graph)[i].first.name, &visited, &Stack);
    }

    GRAPH transposedGraph;
    initializeTranposedGraph(graph, &transposedGraph, index_map);
    AUX_INDEX_MAP new_index_map = setIndexMap(&transposedGraph);
    for (int i = 0; i < (*graph).size(); i++)
    {
        visited[i] = false;
    }
    while (Stack.empty() == false)
    {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false)
        {
            DFS_util(&transposedGraph, &visited, &new_index_map, (transposedGraph)[v].first.name);
            ans++;
        }
    }
    return ans;
}
/*
 * Returns the index of the neighbor with the minimum distance.
 */
int minDistance(GRAPH *graph, std::vector<int> dist, std::vector<bool> sptSet)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < graph->size(); v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

#define INF 1000000000
/*
 * Dijkstra's algorithm that returns the path with the minimum population
 * between the source node "src" and destination node "dest".
 */
int minPopulation(GRAPH *graph, std::string src, std::string dest, AUX_INDEX_MAP *index_map)
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    std::vector<int> dist(graph->size(), INF);

    int current_index = (*index_map)[src];
    int destination_index = (*index_map)[dest];

    pq.push(std::make_pair(0, current_index));
    dist[current_index] = 0;

    // check for self-eating cases
    for (auto &neighbor : (*graph)[current_index].second)
    {
        if (neighbor.food == (*graph)[current_index].first.name)
        {
            dist[current_index] = neighbor.population;
            break;
        }
    }

    // traditional algorithm
    while (!pq.empty())
    {
        int u = pq.top().second; // index
        pq.pop();
        for (auto &neighbor : (*graph)[u].second)
        {
            std::string v = neighbor.food;
            int neighbor_index = (*index_map)[v];
            int neighbor_weight = neighbor.population;
            if (dist[neighbor_index] > dist[u] + neighbor_weight)
            {
                dist[neighbor_index] = dist[u] + neighbor_weight;
                pq.push(std::make_pair(dist[neighbor_index], neighbor_index));
            }
        }
    }
    return dist[destination_index];
}
