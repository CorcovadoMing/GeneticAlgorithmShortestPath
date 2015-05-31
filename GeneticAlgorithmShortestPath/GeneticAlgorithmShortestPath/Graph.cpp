#include "Graph.h"
#include <vector>

void Graph::size(const int size)
{
    size_ = size;
    graph_ = std::vector< std::vector<int> >(size, std::vector<int>(size, 0));
}

void Graph::build(const int from, const int to, const int weight)
{
    graph_[from][to] = weight;
    graph_[to][from] = weight;
}

void Graph::build(const int node, const int weight)
{
    graph_[node][node] = weight;
}

const std::vector<int> Graph::neighbors(const int node, const std::vector<int> &isVisited) const
{
    std::vector<int> neighbors;
    for (std::size_t i = 0; i < graph_[node].size(); i += 1)
    {
        if (graph_[node][i] && !isVisited[i])
            neighbors.push_back((int)i);
    }
    return neighbors;
}

const int Graph::weight(const int from, const int to) const
{
    return graph_[from][to];
}

const int Graph::weight(const int node) const
{
    return graph_[node][node];
}