#include "./../headers/graphAlgorithms.h"

/* creates a set data structure that indexes each name of a graph vertex to its corresponding
 * position in the graph
 *
 * Example: index_table['aardonyx'] = 0, that is, the position of the vertex representing the
 * dinosaur "aardonyx" is 0
 *
 * Helps implement other algorithms
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

/* DFS that returns 1 if there is a path of the "origin" node and that reaches the "destination"
 * node returns 0 otherwise
 */
int recursive_dfs(GRAPH *graph, AUX_INDEX_MAP *index_map, std::vector<bool> &visited,
                  std::string current_node_name, std::string destination_node_name)
{
    // if the current node is the node beign searched for, return find
    if (current_node_name == destination_node_name)
        return 1;

    int current_index = (*index_map)[current_node_name];
    visited[current_index] = true; // mark the current node as visited

    // for each adjacent node, visit it if it has not yet been visited
    for (VECTOR_NODE food_node : (*graph)[current_index].second)
    {
        int destination_index = (*index_map)[food_node.food];
        if (visited[destination_index] == false)
            if (recursive_dfs(graph, index_map, visited, food_node.food, destination_node_name) ==
                1)
                return 1;
    }
    return 0;
}

/* Checks for a path that starts from the source node and arrives at the destination node
 *
 * works as an initializer for the "recursive_dfs" function
 */
int isPath(GRAPH *graph, AUX_INDEX_MAP *index_map, std::string src, std::string dest)
{
    std::vector<bool> visited(index_map->size(), false);
    return recursive_dfs(graph, index_map, visited, src, dest);
}

/* DFS adapted to find the number of cycle components
 *
 * return the number of cycles that leave a vertex origin and arrive at itself
 */
int dfs_number_of_cycles_rec(GRAPH *graph, AUX_INDEX_MAP *index_map, std::vector<bool> &visited,
                             std::string current_node_name, std::string origin_node_name, int *ans)
{
    // current node
    int current_index = (*index_map)[current_node_name];
    visited[current_index] = true; // marking current node as visited

    for (VECTOR_NODE food_node : (*graph)[(*index_map)[current_node_name]].second)
    {
        // if the current node finds the origin_node, increment the answer
        if (food_node.food == origin_node_name)
            (*ans)++;

        // visit other nodes
        if (visited[(*index_map)[food_node.food]] == false)
            dfs_number_of_cycles_rec(graph, index_map, visited, food_node.food, origin_node_name,
                                     ans);
    }
    return 0;
}

/* Function that returns the number of cycles in the given directed graph
 */
int find_number_of_cycles(GRAPH *graph, AUX_INDEX_MAP *IndexMap)
{
    int cycles_num = 0;

    // each iteration count the number of path that leave the origin and arrives at itself
    for (int i = 0; i < graph->size(); i++)
    {
        std::vector<bool> visited(IndexMap->size(), false);
        int aux_ans = 0;
        aux_ans = dfs_number_of_cycles_rec(graph, IndexMap, visited, (*graph)[i].first.name,
                                           (*graph)[i].first.name, &aux_ans);
        cycles_num += aux_ans;
    }

    return cycles_num;
}

/* checks, by brute force, whether a graph is strongly connected or not
 *
 * for each combination of nodes in the graph, it checks to see if there is a path connecting both
 * at the same time
 */
int isStronglyConnected(GRAPH *graph, AUX_INDEX_MAP *index_map)
{
    bool isStrong = true;
    // for each pair of nodes
    for (int i = 0; i < graph->size(); i++)
    {
        for (int j = 0; j < graph->size(); j++)
        {
            // check if there is a path
            if (isPath(graph, index_map, (*graph)[i].first.name, (*graph)[j].first.name) == false)
                isStrong = false;
        }
    }
    return isStrong;
}

// Calculate the number of strongly connected components
//
// brute force approach
int StrongCompsGraph(GRAPH *graph, AUX_INDEX_MAP *index_map)
{
    int ans2 = 0;
    std::vector<bool> is_ssc(graph->size(), false);

    for (int i = 0; i < graph->size(); i++)
    {
        if (!is_ssc[i])
        {
            std::vector<int> scc;
            scc.push_back(i);
            for (int j = 0; j < graph->size(); j++)
            {
                // if there is a path from i to j and a path from j to i
                if (!is_ssc[j] &&
                    isPath(graph, index_map, (*graph)[i].first.name, (*graph)[j].first.name) &&
                    isPath(graph, index_map, (*graph)[j].first.name, (*graph)[i].first.name))
                {
                    is_ssc[j] = true;
                    scc.push_back(j);
                }
            }
            ans2++;
        }
    }
    return ans2;
}

// retorna o index do vizinho com distância mínima
int minDistance(GRAPH *graph, std::vector<int> dist, std::vector<bool> sptSet)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < graph->size(); v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

#define INF 1000000000
// algoritmo de dijskstra
// retorna o caminho com menor população entre o nó src e o nó dest
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

    // modificação para englobar os casos onde uma presa come a si mesma
    for (auto &neighbor : (*graph)[current_index].second)
    {
        if (neighbor.food == (*graph)[current_index].first.name)
        {
            dist[current_index] = neighbor.population;
            break;
        }
    }
    // se a presa não come a si mesma, a distância dela para si mesma é 0.
    // embora conceitualmente errada, é necessária para o algoritmo funcionar e, além disso, o
    //  campo não será importante

    // algoritmo tradicional
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
