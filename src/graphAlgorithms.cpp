#include "./../headers/graphAlgorithms.h"
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <strings.h>
#include <utility>
#include <vector>

AUX_INDEX_MAP setIndexMap(GRAPH *graph)
{
    AUX_INDEX_MAP temp_map;
    for (int i = 0; i < graph->size(); i++)
    {
        // std::cout << (*graph)[i].first.name << " " << i << std::endl;
        temp_map.insert(std::make_pair((*graph)[i].first.name, i));
    }
    return temp_map;
}

int recursive_dfs(GRAPH *graph, AUX_INDEX_MAP *IndexMap, std::string node_name,
                  std::vector<bool> &visited, std::string destino)
{
    // std::cout << "Current Node: " << node_name << ' ' << (*IndexMap)[node_name] << std::endl;
    if (node_name == destino)
        return 1;
    visited[(*IndexMap)[node_name]] = true;
    for (VECTOR_NODE food_node : (*graph)[(*IndexMap)[node_name]].second)
    {
        if (visited[(*IndexMap)[food_node.food]] == false)
            if (recursive_dfs(graph, IndexMap, food_node.food, visited, destino) == 1)
                return 1;
    }
    return 0;
}

int recursive_dfs2(GRAPH *graph, AUX_INDEX_MAP *IndexMap, std::string node_name,
                   std::vector<bool> &visited, std::string destino)
{
    // std::cout << "Current Node: " << node_name << ' ' << (*IndexMap)[node_name] << std::endl;
    if (node_name == destino)
        return 1;
    visited[(*IndexMap)[node_name]] = true;
    for (VECTOR_NODE food_node : (*graph)[(*IndexMap)[node_name]].second)
    {
        if (visited[(*IndexMap)[food_node.food]] == false)
            recursive_dfs(graph, IndexMap, food_node.food, visited, destino);
    }
    return 0;
}

/*void dfs(GRAPH *graph, AUX_INDEX_MAP *IndexMap)
{
    std::vector<bool> visited(IndexMap->size(), false);
    recursive_dfs(graph, IndexMap, "achelousaurus", visited);
}*/

int dfs_number_of_cycles_rec(GRAPH *graph, AUX_INDEX_MAP *IndexMap, std::string node_name,
                             std::vector<bool> &visited, std::set<std::string> *excluded,
                             std::string origin_name, int *i)
{
    // std::cout << "Current Node: " << node_name << ' ' << (*IndexMap)[node_name] << std::endl;
    // int resp = 0;
    visited[(*IndexMap)[node_name]] = true;
    // std::cout << (*graph)[3].first.name << std::endl;
    // std::cout << (*graph)[3].second.size() << std::endl; // 0 ??
    for (VECTOR_NODE food_node : (*graph)[(*IndexMap)[node_name]].second)
    {
        // std::cout << "olhando para a comida: " << food_node.food << " origem: " << origin_name
        //           << std::endl;
        if (food_node.food == origin_name)
            i++;
        // if (((*excluded).contains(food_node.food)) == false &&
        if (visited[(*IndexMap)[food_node.food]] == false)
            dfs_number_of_cycles_rec(graph, IndexMap, food_node.food, visited, excluded,
                                     origin_name, i);
    }
    return 0;
}

int dfs_number_of_cycles(GRAPH *graph, AUX_INDEX_MAP *IndexMap)
{
    int resp = 0;
    std::set<std::string> excluded = {};
    for (int i = 0; i < graph->size(); i++)
    {
        std::vector<bool> visited(IndexMap->size(), false);
        int resp_c = 0;
        dfs_number_of_cycles_rec(graph, IndexMap, (*graph)[i].first.name, visited, &excluded,
                                 (*graph)[i].first.name, &resp_c);
        resp += resp_c;
        excluded.insert((*graph)[i].first.name);
    }
    /*std::vector<bool> visited(IndexMap->size(), false);
    std::cout << dfs_number_of_cycles_rec(graph, IndexMap, "abelisaurus", visited, &excluded,
                                          "abelisaurus")
              << std::endl;
    excluded.insert((*graph)[0].first.name);*/

    return resp;
}

void initializeTranposedGraph(GRAPH *graph, GRAPH *transposedGraph, AUX_INDEX_MAP *indexMap)
{
    for (int i = 0; i < graph->size(); i++)
    {
        (*transposedGraph).push_back((*graph)[i]);
    }
    for (int i = 0; i < graph->size(); i++)
    {
        for (int j = 0; j < (*graph)[i].second.size(); j++)
        {
            std::string food_name = (*graph)[i].second[j].food;
            std::string hunter_name = (*graph)[i].second[j].name;
            VECTOR_NODE temp_node;
            temp_node.name = food_name;
            temp_node.food = hunter_name;
            int index = (*indexMap)[food_name];
            (*transposedGraph)[index].second.push_back(temp_node);
        }
    }
    sortGraph(transposedGraph);
}

int isPath(GRAPH *graph, AUX_INDEX_MAP *index_map, std::string src, std::string dest)
{
    std::vector<bool> visited(index_map->size(), false);
    return recursive_dfs(graph, index_map, src, visited, dest);
}
int isPath2(GRAPH *graph, AUX_INDEX_MAP *index_map, std::string src, std::string dest)
{
    std::vector<bool> visited(index_map->size(), false);
    return recursive_dfs2(graph, index_map, src, visited, dest);
}

int isStronglyConnected(GRAPH *graph, AUX_INDEX_MAP *index_map)
{
    bool isStrong = true;
    for (int i = 0; i < graph->size(); i++)
    {
        for (int j = 0; j < graph->size(); j++)
        {
            if (!isPath(graph, index_map, (*graph)[i].first.name, (*graph)[j].first.name))
                isStrong = false;
        }
    }
    return isStrong;
}

int StrongCompsGraph(GRAPH *graph, AUX_INDEX_MAP *index_map)
{
    GRAPH transposedGraph;
    // initializeTranposedGraph(graph, &transposedGraph, index_map);
    int ans = 0;

    std::vector<bool> is_ssc(graph->size(), false);

    for (int i = 0; i < graph->size(); i++)
    {
        if (!is_ssc[i])
        {
            std::vector<int> scc;
            scc.push_back(i);
            for (int j = i; j < graph->size(); j++)
            {
                if (!is_ssc[j] &&
                    isPath2(graph, index_map, (*graph)[i].first.name, (*graph)[j].first.name))
                {
                    is_ssc[j] = true;
                    scc.push_back(j);
                }
            }
            ans++;
        }
    }
    return ans;
}

int minDistance(GRAPH *graph, std::vector<int> dist, std::vector<bool> sptSet)
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < graph->size(); v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int minPopulation(GRAPH *graph, std::string src, std::string dest, AUX_INDEX_MAP *index_map)
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    std::vector<int> dist(graph->size(), INT32_MAX);

    pq.push(std::make_pair(0, (*index_map)[src]));
    dist[(*index_map)[src]] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (auto &neighbor : (*graph)[u].second)
        {
            std::string v = neighbor.food;
            int weight = neighbor.population;
            if (dist[(*index_map)[v]] > dist[u] + weight)
            {
                dist[(*index_map)[v]] = dist[u] + weight;
                pq.push(std::make_pair(dist[(*index_map)[v]], (*index_map)[v]));
            }
        }
    }
    return dist[(*index_map)[dest]];
}
